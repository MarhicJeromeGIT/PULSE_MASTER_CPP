/*
 * Copyright (C) 2013-2015 Phokham Nonava
 *
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */



#include <string>
#include <iostream>
#include "PulseLib.h"
using namespace std;




int main(int argc, char* argv[]) {
 /* try {
    if (argc == 2) {
      std::string token(argv[1]);
      if (token == "perft") {
        std::unique_ptr<pulse::Perft> perft(new pulse::Perft());
        perft->run();
      }
    } else {
      std::unique_ptr<pulse::Pulse> pulse(new pulse::Pulse());
      pulse->run();
    }
  } catch (std::exception& e) {
    std::cout << "Exiting Pulse due to an exception: " << e.what() << std::endl;
    return 1;
  }*/


	pulse::PulseLib lib;
	lib.startGame();
	//lib.getMoves("e2e4");
	
	vector<pulse::PulseLib::myMove> moves;
	lib.getMoveList( 1, 0, moves );

	lib.drawPos();
	pulse::PulseLib::myMove move(1, 1, 1, 3);
	lib.makeMove(move);
	lib.drawPos();
	lib.play(move);
	lib.drawPos();
	pulse::PulseLib::myMove move2(1, 0, 2, 2);
	lib.makeMove(move2);
	lib.drawPos();
	lib.play(move2);
	lib.drawPos();
/*	char file[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	pulse::PulseLib::myMove move;
	for (int i = 0; i < 1000; i++)
	{
		lib.play(move);
		cout << file[move.origFile] << move.origRank << " -> " << file[move.destFile] << move.destRank << endl;

		if (move.destFile > 7 || move.destRank> 7)
		{
			cout << "prout" << endl;
		}
	}
*/
	system("pause");

}
