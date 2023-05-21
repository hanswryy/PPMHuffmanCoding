Dalam program ini, diimplementasikan algoritma Huffman Code untuk melakukan kompresi gambar. Algoritma ini menggunakan metode kompresi lossless, yang berarti ukuran file gambar dikurangi tanpa mengorbankan kualitas gambar. Algoritma Huffman Code bekerja dengan mengonversi setiap nilai piksel dalam gambar menjadi representasi bit yang lebih pendek. Representasi bit untuk setiap nilai piksel didasarkan pada frekuensi kemunculan nilai piksel tersebut. Niai piksel yang sering muncul akan memiliki representasi bit yang lebih pendek, sedangkan nilai piksel yang jarang muncul akan memiliki representasi bit yang lebih panjang.

Dalam penerapan Huffman Code untuk kompresi gambar, gambar diubah menjadi matriks piksel. Setiap piksel direpresentasikan dengan nilai intensitasnya. Frekuensi kemunculan kombinasi nilai piksel dihitung untuk menentukan prioritas karakter-karakter dalam algoritma Huffman Code. Berdasarkan frekuensi tersebut, pohon Huffman (Binary Tree) dibentuk untuk menentukan kode Huffman untuk setiap karakter. Proses encoding dilakukan dengan menjelajahi matriks piksel dan mengkodekan setiap kombinasi nilai piksel menggunakan kode Huffman yang telah ditentukan. Hasil encoding disimpan dalam file binary.

Untuk melakukan decoding, file binary hasil kompresi dibaca dan pohon Huffman digunakan untuk mendekode setiap kombinasi nilai piksel. Matriks piksel dikembalikan ke bentuk aslinya, sehingga gambar dapat direkonstruksi. Kompresi gambar dengan menggunakan Huffman Code menghasilkan file gambar yang lebih kecil dibandingkan dengan file gambar asli. Namun, perlu dicatat bahwa Huffman Code hanya dapat digunakan untuk kompresi lossless, yang berarti kualitas gambar tidak dikorbankan. Oleh karena itu, algoritma ini lebih cocok digunakan untuk gambar-gambar dengan struktur sederhana dan tidak terlalu kompleks.

Demo Program

Proses Encoding
  _  _       __  __                    ___         _
 | || |_  _ / _|/ _|_ __  __ _ _ _    / __|___  __| |___
 | __ | || |  _|  _| '  \/ _` | ' \  | (__/ _ \/ _` / -_)
 |_||_|\_,_|_| |_| |_|_|_\__,_|_||_|  \___\___/\__,_\___|

Kompresi File Gambar Berformat PPM dengan Metode Huffman Coding
                PPM to TXT & TXT to PPM
Oleh : Farhan Muhammad Luthfi, Faris Abulkhoir, Mahardika Pratama
        Jurusan Teknik Komputer dan Informatika
                Politeknik Negeri Bandung
                        Angkatan 22


                        1. Encode
                        2. Decode
                        3. Quit

                        Enter your choice: 1

                        Write the file name : test2.ppm
                        Loading...
                        Nama file original : test2.ppm
                        Ukuran file original : 367515 bytes
                        Nama file kompresi : test2.txt
                        Ukuran file kompresi : 137409 bytes
                        Persentase pengurangan size : 37.388680 persen
                        Encode Finish, press any key to continue...
                     
Proses Decoding
