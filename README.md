# 🚨 Flood Monitoring System with Blynk & ESP32

Sistem ini merupakan proyek simulasi **monitoring ketinggian air** menggunakan **ESP32**, **sensor ultrasonik HC-SR04**, serta integrasi **dashboard Blynk** sebagai media visualisasi dan kontrol jarak jauh. Sistem dirancang untuk mendeteksi potensi banjir secara real-time dan memberikan notifikasi kepada pengguna melalui aplikasi Blynk saat ketinggian air melebihi ambang batas yang telah ditentukan.

## 🛠️ Fitur Utama
- Deteksi ketinggian air menggunakan HC-SR04
- Kirim notifikasi otomatis ke HP pengguna via Blynk saat tinggi air melebihi batas
- Tampilan data ketinggian air real-time di dashboard Blynk (Virtual Pin V1)
- Kontrol manual notifikasi melalui tombol virtual (Virtual Pin V0)
- Aktivasi otomatis LED dan buzzer sebagai alarm lokal saat terjadi kenaikan air

## 🔧 Komponen yang Digunakan
- ESP32 Dev Board
- Sensor Ultrasonik HC-SR04
- LED indikator (merah)
- Buzzer
- Aplikasi Blynk
- WiFi (simulasi menggunakan Wokwi)

## 🔄 Cara Kerja Sistem

```mermaid
flowchart TD
    A[Mulai] --> B[HP User terkoneksi dengan dashboard Blynk]
    B --> C[ESP32 terhubung ke Blynk dan mulai membaca sensor]
    C --> D[Sensor HC-SR04 mengukur jarak air]
    D --> E[Jarak diproses oleh ESP32]
    E --> F{Apakah kondisi air terlalu tinggi?}
    F -->|YA| G[LED menyala\nBuzzer berbunyi\nKirim notifikasi via Blynk]
    F -->|TIDAK| H[LED mati\nBuzzer mati]
    G --> I[Tampilan dashboard:\n- Data tinggi air\n- Tombol kontrol notifikasi]
    H --> I
    I --> J[Sistem memantau ulang siklus]
    J --> D
```
note: Project lomba PKM AI OIM FTUI 2025
