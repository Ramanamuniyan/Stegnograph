# Stegnograph
# BMP Steganography (Encode & Decode)

This project implements **image steganography** in C using the **Least Significant Bit (LSB)** technique.  
You can **encode a secret file** (any type: text, pdf, image, etc.) into a `.bmp` image and later **decode it** back.

---

## 📌 Features
- Encode any secret file into a 24-bit BMP image
- Decode and extract the hidden file from a stego BMP
- Supports secret file extension detection and auto-reconstruction
- Preserves the BMP header and pixel data integrity
- Error handling for file operations and capacity checks

---

## 🛠️ Requirements
- GCC (or any C compiler)
- Linux / Ubuntu (tested)
- 24-bit BMP image as source cover file

---

## 📂 Project Structure
```
├── encode.c        # Encoding functions
├── decode.c        # Decoding functions
├── encode.h        # Encode header file
├── decode.h        # Decode header file
├── types.h         # Common data structures and enums
├── main.c          # Entry point
├── Makefile        # To build project
└── README.md       # Documentation
```

---

## ⚙️ Build Instructions

Clone this repository and build:

```bash
git clone https://github.com/<your-username>/<repo-name>.git
cd <repo-name>
make
```

This will generate two executables:
- `steg_encode`
- `steg_decode`

---

## ▶️ Usage

### Encoding
Hide a secret file inside a BMP image.

```bash
./steg_encode -e <source.bmp> <secret_file> <output_stego.bmp>
```

Example:
```bash
./steg_encode -e input.bmp secret.txt stego.bmp
```

---

### Decoding
Extract the secret file from the stego BMP.

```bash
./steg_decode -d <stego.bmp>
```

Example:
```bash
./steg_decode -d stego.bmp
```

This will create a file named `decode_file.<ext>` where `<ext>` is the original extension of the hidden file.

---

## 🧪 Example Workflow

```bash
# Encode
./steg_encode -e lena.bmp notes.txt stego.bmp

# Decode
./steg_decode -d stego.bmp
# Output → decode_file.txt
```

---

## 🚧 Limitations
- Works only with **24-bit BMP images**
- The cover image must be large enough to hold the secret file
- Currently assumes header size = 54 bytes (standard BMP); some BMP variants may differ

---



---

## 👨‍💻 Author
- Ramana

---

## 📑 Header Files

### encode.h
- Contains the `EncodeInfo` structure used during encoding
- Defines constants for buffer sizes and ANSI color codes:
  - `RESET`, `RED`, `GREEN` (for colored console messages)
- Declares all encoding-related functions such as:
  - `check_operation_type()`
  - `read_and_validate_encode_args()`
  - `do_encoding()`
  - `open_files()`, `check_capacity()`
  - `encode_magic_string()`, `encode_secret_file_extn()`, `encode_secret_file_data()`
  - `encode_byte_to_lsb()`, `encode_size_to_lsb()`
  - `copy_remaining_img_data()`
  - 
