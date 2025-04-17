const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');
const scoreElement = document.getElementById('score');
const cellSize = 20;

let gameState = {
    snake: [],
    food: {x: 0, y: 0},
    score: 0,
    gameOver: false
};

// Управление с клавиатуры
document.addEventListener('keydown', (e) => {
    if (gameState.gameOver) return;
    
    let direction;
    switch(e.key) {
        case 'ArrowUp': direction = 'UP'; break;
        case 'ArrowDown': direction = 'DOWN'; break;
        case 'ArrowLeft': direction = 'LEFT'; break;
        case 'ArrowRight': direction = 'RIGHT'; break;
        default: return;
    }
    
    fetch('/control', {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({direction})
    });
});

// Рестарт по клику
canvas.addEventListener('click', () => {
    if (gameState.gameOver) {
        fetch('/control', {
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify({action: 'restart'})
        });
    }
});

// Отрисовка игры
function drawGame() {
    // Очистка холста
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    
    // Отрисовка змейки
    ctx.fillStyle = 'green';
    gameState.snake.forEach(segment => {
        ctx.fillRect(segment.x * cellSize, segment.y * cellSize, cellSize, cellSize);
    });
    
    // Отрисовка еды
    ctx.fillStyle = 'red';
    ctx.fillRect(gameState.food.x * cellSize, gameState.food.y * cellSize, cellSize, cellSize);
    
    // Счёт
    scoreElement.textContent = gameState.score;
    
    // Сообщение о конце игры
    if (gameState.gameOver) {
        ctx.fillStyle = 'rgba(0, 0, 0, 0.7)';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        ctx.fillStyle = 'white';
        ctx.font = '30px Arial';
        ctx.textAlign = 'center';
        ctx.fillText('GAME OVER - CLICK TO RESTART', canvas.width/2, canvas.height/2);
    }
}

// Обновление состояния игры
async function updateGame() {
    try {
        const response = await fetch('/state');
        const data = await response.json();
        
        gameState = {
            snake: data.snake.map(s => ({x: s.x, y: s.y})),
            food: {x: data.food.x, y: data.food.y},
            score: data.score,
            gameOver: data.gameOver
        };
        
        drawGame();
        requestAnimationFrame(updateGame);
    } catch (error) {
        console.error('Error:', error);
        setTimeout(updateGame, 1000); // Повтор через 1 сек при ошибке
    }
}

// Запуск игры
updateGame();
