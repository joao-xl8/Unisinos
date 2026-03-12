#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

int main(int argc, char *arcv[])
{
    pid_t id = fork();
    if (id == -1)
        return -1;

    if (id == 0)
    {
        std::string target_word = "Brasil";
        std::string command = "curl -s https://www.cnnbrasil.com.br/ | egrep -o '" + target_word + "' | wc -l";

        execl(
            "/bin/sh",
            "sh",
            "-c",
            command.c_str(),
            nullptr);
        std::cout << "Se chegar aqui exec falhou" << std::endl;
    }
    else
    {
        int N = 10;
        int matrix[N][N];
        srand(time(nullptr));
        // std::cout << "Matriz original:" << std::endl;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                matrix[i][j] = rand() % 100;
                // std::cout << matrix[i][j] << " ";
            }
            // std::cout << std::endl;
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
        std::cout << "Matriz transposta:" << std::endl;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        wait(nullptr);
    }

    return 0;
}