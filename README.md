# 🧭 NaviBot – Smart Campus Navigation System

**NaviBot** is a smart campus navigation system designed to help students and visitors easily find locations within Sathyabama University's campus. The system combines **IoT hardware**, **web-based navigation**, and a **chatbot interface** to deliver a seamless scan-to-navigate experience.

Built as a practical prototype, NaviBot demonstrates how embedded systems and web technologies can work together to solve real-world navigation problems in large educational campuses.

---

## 🚀 Prototype Images / Demonstration

![Image](https://github.com/user-attachments/assets/9a8a016f-2f50-4bbb-be5d-dd4c8a5977d7)



---

## 🧠 How It Works

1. The **ESP32** displays a QR code on an **OLED display**
2. User scans the QR code using a mobile device
3. The web interface opens with a **campus navigation map**
4. User selects **source and destination**
5. The system computes the **shortest path using Dijkstra’s Algorithm**
6. The route is visually displayed on the campus map
7. A **chatbot** assists with campus-related queries

![Image](https://github.com/user-attachments/assets/e5341f60-cba3-4ed2-8ad3-365d5c41e8a4)
<img src="https://github.com/user-attachments/assets/72c29441-1b95-4712-8790-e7656232ed05" width="400" height='523'/>
![Image](https://github.com/user-attachments/assets/df9d0c90-c895-4490-ac4a-a072fe1da228)
<img src="https://github.com/user-attachments/assets/b974ee6f-b667-4d13-b06c-ad34af7f26ee" width="400" height='600'/>


---

## 🛠️ Flow Diagram

---

## ✨ Features

* 📍 Campus navigation using **Google Satellite Image API**
* 🧠 Shortest path calculation using **Dijkstra’s Algorithm**
* 📱 QR-based instant access (ESP32 + OLED)
* 💬 Integrated chatbot using **Chatbase**
* 🌐 Lightweight, responsive web interface
* 🔌 Hardware–software integration for real-world deployment

---

## 🛠️ Tech Stack

### Frontend

* HTML
* CSS

### APIs & Services

* Google Satellite Image API (map base)
* Chatbase (AI chatbot)

### Hardware

* ESP32 Microcontroller
* OLED Display
* Laptop running Arduino IDE

### Development Tools

* Arduino IDE (C/C++ for ESP32)
* Web browser (testing & deployment)

---

## 🧩 System Architecture

* **ESP32** handles QR code generation and display
* **Web Interface** manages user interaction and routing
* **Pathfinding Logic** computes shortest routes between nodes
* **Chatbot Layer** provides conversational assistance

---

## 📌 Project Status

✅ Prototype / MVP
This project is currently a functional prototype intended for demonstration and academic evaluation.

---

## 🔮 Future Enhancements

* Real-time GPS-based navigation
* Offline campus maps
* Automatic node mapping
* Improved UI/UX
* Multi-campus scalability
* Voice-based navigation support

---

## 👨‍💻 Author

**Shreyas S**, 3rd Year Undergraduate<br>
Student Developer | Web • ML • AI • Game Dev

---

## 📄 License

MIT License

Copyright (c) 2025 Shreyas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---
