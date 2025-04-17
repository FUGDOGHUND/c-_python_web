import unittest
import requests
import time

class TestGame(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.base_url = "http://localhost:8080"
        
    def test_web_interface(self):
        response = requests.get(f"{self.base_url}/")
        self.assertEqual(response.status_code, 200)
        self.assertIn("<!DOCTYPE html>", response.text)
        
    def test_game_logic(self):
        # Тестирование движения змейки
        response = requests.post(f"{self.base_url}/control", 
                               json={"direction": "RIGHT"})
        self.assertEqual(response.status_code, 200)
        
        time.sleep(0.1)
        state = requests.get(f"{self.base_url}/state").json()
        self.assertGreater(state["snake"][0]["x"], 10) # Начальная позиция X

if __name__ == "__main__":
    unittest.main()