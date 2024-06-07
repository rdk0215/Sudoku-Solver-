#include <bits/stdc++.h> 

using namespace std;

int mat[9][9];
int notes[9][9][10];
int marked = 0;

ifstream inp("input.txt");
ofstream out("output.txt");

void initialise_notes(){
    for(int row = 0; row <= 8; row++)
		for(int column = 0; column <= 8; column++)
			if(mat[row][column] == 0)
			{
				for(int digit = 1; digit <= 9; ++digit)
				{
					bool added = 1;
					for(int ii = 0; ii <= 8; ii++)
						if(mat[ii][column] == digit)
							added = 0;
					for(int jj = 0; jj <= 8; jj++)
						if(mat[row][jj] == digit)
							added = 0;
					for(int ii = (row/3)*3; ii <= (row/3)*3 + 2; ii++)
						for(int jj = (column/3)*3; jj <= (column/3)*3 + 2; jj++)
							if(mat[ii][jj] == digit)
								added = 0;
					notes[row][column][digit] = added;
				}
			}
}
 

bool found;
void brute(int L, int C)
{
    if (found)
        return;
    if (L == 9)
    {
        found = 1;
        // print_solution();
        return;
    }
    if (mat[L][C] != 0)
    {
        if (C == 8)
            brute(L + 1, 0);
        else
            brute(L, C + 1);
    }
    else
    {
        for (int digit = 1; digit <= 9 && !found; ++digit)
            if (notes[L][C][digit] == 1)
            {
                bool added = 1;
                for (int pos_line = 0; pos_line <= 8; ++pos_line)
                    if (mat[pos_line][C] == digit)
                        added = 0;

                for (int pos_column = 0; pos_column <= 8; ++pos_column)
                    if (mat[L][pos_column] == digit)
                        added = 0;

                for (int pos_line = ((L/3)*3); pos_line <= ((L/3)*3) + 2; ++pos_line)
                    for (int pos_column = ((C/3)*3); pos_column <= ((C/3)*3) + 2; ++pos_column)
                        if (mat[pos_line][pos_column] == digit)
                            added = 0;

                if (added)
                {
                    mat[L][C] = digit;
                    if (C == 8)
                        brute(L + 1, 0);
                    else
                        brute(L, C + 1);
                    if (found)
                        return;
                    mat[L][C] = 0;
                }
            }
    }
}


void print_solution(){
        out << "Done" << endl;
        for(int row = 0; row <= 8; row++){
            for(int column = 0; column <= 8; column++){
                out << mat[row][column] << " ";
            }
        
        out << endl;
        }
}
void solve_sudoku(){
        // for(int row = 0; row < 9; row++){
        //     for(int column = 0; column < 9; column++){
        //         if(mat[row][column]){
        //             marked++;
        //         }
        //     }
        // }

        initialise_notes();


        // while(marked != 81){

        //     check_column();
        //     check_row();
        //     check_3x3();
        //     one_val();
        // }

        // for(int row = 0; row <= 8; row++)
		// 	for(int column = 0; column <= 8; column++)
		// 		if(mat[row][column] != 0)
		// 			org[line][column] = 1;
		brute(0, 0);

}


int main(){

        int test; inp >> test;

        for(int i = 0; i < test; i++){
            string grid; 
            inp >> grid;

        for(int row = 0; row < 9; row++){
            for(int column = 0; column < 9; column++){
                int pos = row * (9) + column ; 
                if( grid[pos] == '0'){
                    mat[row][column] = 0;}
                else{
                    mat[row][column] = (grid[pos] - '0') ; 
                }
            }
        }


        solve_sudoku();

        bool done = 1;

        for(int row = 0; row <= 8; row++){
            for(int column = 0; column <= 8; column++){

                if(mat[row][column] == 0){
                    done = 0; 
                }
            }
        }

        if(done){
            print_solution();
        } 


        }

}
