# Questions

## What's `stdint.h`?

This header defines a set of integral type aliases with specific width requirements, along with macros specifying their limits and macro functions to create values of these types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Integer type with a width of exactly 8, 16, 32, or 64 bits. No padding bits.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE:1byte; DWORD:4 bytes; LONG:4 bytes; WORD:2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM

## What's the difference between `bfSize` and `biSize`?

bfSize = biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
biSizeImage = (biWidth * sizeof(RGBTRIPLE) + padding) * abs(biHeight)

## What does it mean if `biHeight` is negative?

For uncompressed RGB bitmaps, if biHeight is positive, the bitmap is a bottom-up DIB with the origin at the lower left corner.
If biHeight is negative, the bitmap is a top-down DIB with the origin at the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The biBitCount member of the BITMAPINFOHEADER structure determines the number of
bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Infile might not exist.

## Why is the third argument to `fread` always `1` in our code?

The third argument is count: the number of the objects to be read.
In this case it's 1 because we read one pixel at a time.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

skip over padding, if any

## What is `SEEK_CUR`?

the current position indicator

## Whodunit?

It was professor Plum with the candlestick in the library.
