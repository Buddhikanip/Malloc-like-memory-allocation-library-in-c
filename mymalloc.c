#include <stddef.h>

char ram[25000];

struct data
{
    void *block_ptr;
    void *data_ptr;
    int data_size;
    struct data *next;
    //struct data *prev;m
};

void *Start = ram;
void *End = ram;
void *ptr = ram;
int tot = 0, counter = 0;

int available(int); // check if poiner exceed the 25000 limit
int is_fill(int);
int is_full(int); // check if allocation space availble in the ram
void merge();

void *MyMalloc(int size)
{
    if (available(size))
    {
        struct data *block, *temp;
        block = (struct data *)ptr;

        block->block_ptr = ptr;
        block->data_ptr = ptr + sizeof(struct data);
        block->data_size = size;

        if (ptr == Start)
        {
            block->next = 0x0;
            //block->prev = 0x0;
            End = block;
        }
        else
        {
            temp = (struct data *)End;
            temp->next = block;
            //block->prev = temp;
            block->next = 0x0;
            End = block;
        }

        tot = tot + size + sizeof(struct data);
        ptr = ptr + size + sizeof(struct data);

        counter++;
        return block->data_ptr;
    }
    else
    {
        if (is_full(size))
            return NULL;
        else
        {
            struct data *block, *temp;
            block = (struct data *)Start;

            int i, j = 0;
            for (i = 0; i < counter; i++)
            {
                if (block->data_size < 0)
                {
                    int free_size = 0 - block->data_size;

                    if (free_size == size)
                    {
                        block->data_size = 0 - block->data_size;
                        tot = tot + size;
                        return block->data_ptr;
                    }
                    else if (free_size > size)
                    {
                        if (free_size - size > sizeof(struct data))
                        {
                            temp = (struct data *)(block->data_ptr + size);

                            temp->block_ptr = (block->data_ptr + size);
                            temp->data_ptr = temp->block_ptr + sizeof(struct data);
                            temp->data_size = 0 - (free_size - size - sizeof(struct data));
                            temp->next = block->next;
                            //temp->prev = block;

                            block->data_size = size;
                            //block->next->prev = temp;
                            block->next = temp;

                            counter++;
                            tot = tot + size + sizeof(struct data);
                            return block->data_ptr;
                        }
                        else
                        {
                            // poddk case memory waste & wadiyen denwa
                            //internal fragmentation
                            block->data_size = 0 - block->data_size;
                            tot = tot + size;
                            return block->data_ptr;
                        }
                    }
                    else
                    {
                        block = block->next;
                    }
                }
                else
                    block = block->next;
            }
            return NULL;
        }
    }
}

void MyFree(void *fptr)
{
    struct data *block;
    block = (struct data *)Start;

    while (block->data_ptr != fptr)
        block = block->next;

    int i;
    char *temp = (char *)block->data_ptr;
    for (i = 0; i < block->data_size; i++, temp++)
        *temp = '\000';

    block->data_size = 0 - block->data_size;
    tot = tot + block->data_size;
    merge();
    merge();
}

int available(int size)
{
    if (is_fill(size))
        return 0;
    else
        return 1;
}

int is_fill(int size)
{
    if (ptr + size >= Start + 25000)
        return 1;
    else
        return 0;
}

int is_full(int size)
{
    if (tot + size >= 25000)
        return 1;
    else
        return 0;
}

void merge()
{
    struct data *block, *temp1, *temp2;
    block = (struct data *)Start;

    int i, j;
    for (i = 0; i < counter - 1; i++)
    {
        if (block->data_size <= 0)
        {
            temp1 = (struct data *)(block->data_ptr - block->data_size);
            temp2 = temp1->next;
            if (temp1->data_size <= 0)
            {
                block->next = temp2;
                //temp2->prev = block;
                block->data_size = temp1->data_size + block->data_size - sizeof(struct data);
                counter--;

                char *temp = (char *)block->data_ptr;
                int size = 0 - block->data_size;
                for (j = 0; j < size; j++, temp++)
                    *temp = '\000';
                tot = tot - sizeof(struct data);
            }
            else
                block = block->next;
        }
        else
            block = block->next;
    }
}