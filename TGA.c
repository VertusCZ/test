

void save_pgm(char* filename, Pixel* pixels, unsigned char* arr, int cols, int rows, int scale)
{
    char buff[255];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[i * cols + j] = 0.3*pixels[i * cols + j].R +
                                0.6*pixels[i * cols + j].G +
                                0.1*pixels[i * cols + j].B;
        }
    }

    FILE* file = fopen(filename, "wb");
    sprintf(buff, "%s\n%d %d\n%d\n", "P5", cols, rows, scale);
    fwrite(buff, sizeof(unsigned char), strlen(buff), file);
    fwrite(arr, sizeof(unsigned char), rows * cols, file);
    fclose(file);
}

int main(void) {
    srand(time(NULL));
    uint16_t rows = 500;
    uint16_t cols = 1000;

    TGA_Header header = {0,0,2,0,0,0,0,0, cols, rows,24,0};
    Pixel* pixels = (Pixel*) malloc(sizeof(Pixel) * rows * cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            pixels[i * cols + j].R = rand() % 255;
            pixels[i * cols + j].G = rand() % 255;
            pixels[i * cols + j].B = rand() % 255;
        }
    }

    for (int j = 0; j < cols; j++)
    {
        pixels[rows / 4 * cols + j].R = 0;
        pixels[rows / 4 * cols + j].G = 0;
        pixels[rows / 4 * cols + j].B = 0;
    }

    save_TGA(header, pixels, rows, cols, "image.tga");
    load_TGA(&header, &pixels, "image.tga");
    rows = header.width;
    cols = header.height;
    unsigned char* arr = (unsigned char*) malloc(sizeof(unsigned char) * rows * cols);
    save_pgm("image.pgm", pixels, arr, rows, cols, 255);

    free(pixels);
    pixels = NULL;
    free(arr);
    arr = NULL;

    return 0;
}