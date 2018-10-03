#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;

/// Using Uston APC System for card counting

int ten_side_count (char card) {
    switch(card) {
        case 'K':
        case 'Q':
        case 'J':
        case 'T': return -9;
    }
    return 4;
}

int counting_system (char card) {
    switch(card) {
        case 'A': return 0;
        case 'K': return -3;
        case 'Q': return -3;
        case 'J': return -3;
        case 'T': return -3;
        case '9': return -1;
        case '8': return 1;
        case '7': return 2;
        case '6': return 2;
        case '5': return 3;
        case '4': return 2;
        case '3': return 2;
        case '2': return 1;
    }
    return 0;
}

int main()
{
    double decks, wager;
    cout << "Number of Decks: ";
    cin >> decks;
    cout << "Base Bet: ";
    cin >> wager;   cin.ignore();
    cout << "Q to quit, R to reset";
    while (true) {
        const double cards_in_deck = 52.0;
        string hand = "L";
        double cards_left = cards_in_deck * decks;
        int running_count = 0, aces = decks * 4, insurance_count = 0;

        while (true) {
            cout << "\n\nEnter Cards: ";
            getline(cin, hand);
            if (hand == "R" || hand == "r")
                {cout << "\n\n[RESET]\n\n"; break;}
            if (hand == "Q") return 0; /// program exit

            for (unsigned int i = 0; i < hand.length(); i++) {
                char card = toupper(hand.at(i));

                /// SPEED-INPUT
                if (card == '+' || card == '0') card = 'T';
                else if (card == '1') card = 'A';

                if (card == 'A') aces--; /// # Aces
                running_count += counting_system(card);
                insurance_count += ten_side_count(card);
            }
            cards_left -= hand.length();
            double true_count = cards_in_deck * running_count / cards_left / 2;

            /// True Count is rounded down to 2 decimals
            /// determined by dividing running count by half-decks
            printf("True Count: %.2f | Decks Left: %.2f", true_count, (cards_left / cards_in_deck));

            printf(" | Excess Aces: %.1f | INSURANCE: ", aces - cards_left / 13);
            if (insurance_count > 4 * cards_left / cards_in_deck)
                cout << "YES\n";
            else cout << "NO\n";

            /// Wagering Count uses excess aces

            double wager_count =
            cards_in_deck * (running_count + 3 * (aces - cards_left / 13))
            / cards_left / 2;

            if (wager_count < 1) {cout << "Bet minimum.";}
            else {
                printf("Bet %.1f.", wager_count * wager);
                if ((wager_count*wager*1.15/2)>=wager)
                    {printf(" | (2 seats): %.1f", wager_count*wager*1.15/2);
                }
                if ((wager_count*wager*1.26/2)>=wager) {
                    printf(" | (4 seats): %.1f", wager_count*wager*1.26/2);}
            }


        }
    }
}
