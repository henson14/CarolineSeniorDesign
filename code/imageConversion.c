#include "imageConversion.h"

bool ConvertToBin(char *filename, int * dimensions) {
    char textFile[256];
    char bmpFile[256];
    char binFile[256];
    sprintf(textFile, "Text Images/%s.txt", filename);
    sprintf(bmpFile, "BMP Images/%s.bmp", filename);
    sprintf(binFile, "Binary Images/%s.bin", filename);

    FILE *file = fopen(textFile, "r");
    SDL_Surface *image = SDL_LoadBMP(bmpFile);

    if (file == NULL || image == NULL) {
        printf("Failed to open files: %s\n", filename);
        return false;
    }

    int rows = image->h;
    int cols = image->w;
    dimensions[0] = rows;
    dimensions[1] = cols;

    // Dynamically allocate a 1D array to store the pixel values
    uint8_t *pixels = (uint8_t *)malloc(rows * cols * sizeof(uint8_t));
    if (pixels == NULL) {
        printf("Failed to allocate memory for pixels array.\n");
        fclose(file);
        SDL_FreeSurface(image);
        return false;
    }

    // Read in each line and store the values in the array
    char line[1024];
    for (int i = 0; i < rows; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            char *token = strtok(line, ",");
            for (int j = 0; j < cols && token != NULL; j++) {
                pixels[i * cols + j] = (uint8_t)atoi(token); // convert from char to unsigned integer
                token = strtok(NULL, ",");
            }
        }
    }

    // Write the pixel values to a binary file
    FILE *writeBinaryFile = fopen(binFile, "wb");
    if (writeBinaryFile == NULL) {
        printf("Failed to open the binary file\n");
        free(pixels);
        fclose(file);
        SDL_FreeSurface(image);
        return false;
    }
    fwrite(pixels, sizeof(uint8_t), rows * cols, writeBinaryFile);
    printf("File %s written successfully.\n", binFile);

    // Clean up
    free(pixels);
    fclose(writeBinaryFile);
    fclose(file);
    SDL_FreeSurface(image);

    return true;
}

bool CheckBin(char *filename, int * dimensions, bool print)
{
    // Open the binary file for reading
    char binFile[256];
    sprintf(binFile, "%s/%s.bin", "Binary Images", filename);
    FILE *readBinaryFile = fopen(binFile, "rb");
    if (readBinaryFile == NULL) {
        printf("Failed to open the binary file for reading\n");
        return false;
    }

    // Create a 1D array to store the pixel values
    uint8_t *read_pixels = (uint8_t *)malloc(dimensions[0] * dimensions[1] * sizeof(uint8_t));
    if (read_pixels == NULL) {
        printf("Failed to allocate memory for read_pixels array.\n");
        fclose(readBinaryFile);
        return false;
    }

    // Read the pixel values from the binary file
    size_t elementsRead = fread(read_pixels, sizeof(uint8_t), dimensions[0] * dimensions[1], readBinaryFile);
    if (elementsRead != dimensions[0] * dimensions[1]) {
        printf("Failed to read the correct number of elements from the binary file\n");
        printf("Expected: %d, Read: %ld\n", dimensions[0] * dimensions[1], elementsRead);
        free(read_pixels);
        fclose(readBinaryFile);
        return false;
    }

    // Close the binary file
    fclose(readBinaryFile);

    // Print the pixel values if requested
    if (print) {
        for (int i = 0; i < dimensions[0]; i++) {
            for (int j = 0; j < dimensions[1]; j++) {
                printf("%hhu ", read_pixels[i * dimensions[1] + j]);
            }
            printf("\n");
        }
    }

    // Clean up
    free(read_pixels);

    return true;
}
