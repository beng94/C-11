#include <cstdio>

class FilePtr
{
    private:
        FILE *file = 0;
    public:
        FilePtr () = default;

        void operator= (FILE* rhs)
        {
            this->file = rhs;
        }

        operator FILE* ()
        {
            return file;
        }

        ~FilePtr()
        {
            fclose(this->file);
        }

        void operator= (FilePtr) = delete;
        FilePtr (const FilePtr&) = delete;
};

void fclose(FilePtr) = delete;

int main()
{
    FilePtr fp;

    fp = fopen("hello.txt", "wt");
    fprintf(fp, "Hello vilag");
    fclose(fp);

    return 0;
}
