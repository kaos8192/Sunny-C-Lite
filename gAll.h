#include <vector>

#ifndef GENERATOR_H
#define GENERATOR_H

void make_point(int x, int y);
void make_rect(int tlx, int tly, int w, int l);

class Code_Vect
{
    private:
        std::vector<int> code;
    public:
        void add(int x, int y);
        void sub(int x, int y);
        int get_size();
};

#endif
