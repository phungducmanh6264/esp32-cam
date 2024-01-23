#include <WiFi.h>
#include <WiFiClient.h>
#include "Camera.h"
#include "esp_camera.h"

const char* SSID = "HOA SEN";
const char* PASSWORD = "55599888";
const char* SERVERIP = "192.168.1.7";
const int SERVERPORT = 12345;

WiFiClient client;

void setup() {

  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Đang kết nối WiFi...");
  }
  Serial.println("Kết nối WiFi thành công!");

  if (client.connect(SERVERIP, SERVERPORT)) {
    Serial.println("Kết nối đến server thành công!");
  } else {
    Serial.println("Lỗi kết nối đến server!");
  }

  // send int
  // client.print(3390);
  // client.print(124357986);

  MyInitCamera();
}

void loop() {
  camera_fb_t* fb =  esp_camera_fb_get();
    if (fb) {
      size_t width = fb->width;    // Chiều rộng của hình ảnh
      size_t height = fb->height;  // Chiều cao của hình ảnh
      size_t len = fb->len;        // Kích thước dữ liệu hình ảnh
      // uint8_t* pixels = fb->buf;   // Con trỏ đến dữ liệu hình ảnh

      printf("Image size (%zu x %zu)\n", width, height);
      printf("Buf len: %zu\n", len);

      // client.print("Hello world couint how are you to day?");
      Serial.println("Đang gửi ảnh...");

      client.print(String(len));
      client.write((const char*)fb->buf, len);
      Serial.println("Đã gửi ảnh");

      esp_camera_fb_return(fb);

      // client.write((uint8_t*)&fb->len, sizeof(fb->len));
      // client.print(String(fb->len));
      // client.write(pixels, len);

    } else {
      Serial.println("Không đọc được hình ảnh");
    }
    Serial.println("Đang chờ cho lần đọc hình ảnh tiếp theo.");
  delay(1000);
}
