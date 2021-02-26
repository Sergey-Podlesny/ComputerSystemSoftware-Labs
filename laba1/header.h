//
// Created by s3rp0d on 19/02/2021.
//

#ifndef SPOVM_1_HEADER_H
#define SPOVM_1_HEADER_H
struct Telephone{
    double regionalCost; // cost per 1 minute of regional calling
    double localCost; // cost per 1 minute of local calling
};



struct Men {
    double currentMoneyCount;
    struct Telephone* telephone;


};

void setData(struct Men* men, double regionalCost, double localCost, double currentMoneyCount);
void pushMoney(struct Men* men, double count);
int regionalCall(struct Men* men, double minute);
int localCall(struct Men* men, double minute);

void menu();

void debug(struct Men* men);

#endif //SPOVM_1_HEADER_H
