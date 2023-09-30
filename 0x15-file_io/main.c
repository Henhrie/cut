#include "main.h"

/**
 * main - Entry point for copying a file or displaying ELF header
 * @ac: Number of arguments
 * @av: Array of arguments
 * Return: 0 on success, otherwise appropriate error code
 */
int main(int ac, char **av)
{
    if (ac != 3)
    {
        dprintf(STDERR_FILENO, "Usage:\n");
        dprintf(STDERR_FILENO, "  To copy a file: %s file_from file_to\n", av[0]);
        dprintf(STDERR_FILENO, "  To display ELF header: %s elf_filename\n", av[0]);
        return (EXIT_FAILURE);
    }

    if (is_elf_file(av[1]))
    {
        int elf_fd;
        Elf64_Ehdr header;

        elf_fd = open(av[1], O_RDONLY);
        if (elf_fd == -1)
        {
            dprintf(STDERR_FILENO, "Error: Cannot open file %s\n", av[1]);
            return (EXIT_FAILURE);
        }

        if (read(elf_fd, &header, sizeof(header)) != sizeof(header))
        {
            dprintf(STDERR_FILENO, "Error: Cannot read ELF header\n");
            close(elf_fd);
            return (EXIT_FAILURE);
        }

        display_elf_info(&header);

        close(elf_fd);
        return (EXIT_SUCCESS);
    }
    else
    {
        int file_from, file_to;
        ssize_t n;
        char buffer[1024]; // Buffer to hold read data

        file_from = open(av[1], O_RDONLY);
        file_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);

        error_file(file_from, file_to, av);

        while ((n = read(file_from, buffer, sizeof(buffer))) > 0)
        {
            if (write(file_to, buffer, n) != n)
            {
                error_file(-1, file_to, av);
            }
        }

        close(file_from);
        close(file_to);

        return (EXIT_SUCCESS);
    }
}