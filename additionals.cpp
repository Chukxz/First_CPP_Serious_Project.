#include <iostream>
#include <string>
using namespace std;



// class Lesser{
//     private:
//     int num = 40;
//     public:
//     Lesser(double n){
//         this->recurse(n);
//     }
//     void recurse(double n){
//         double vald = num / n;
//         int vali = vald;
//         double remd = (vald - vali)*10;
//         if(remd>1){

//         }
// };



class Round{
    private:
    double nd;
    int ni;
    double rem;
    double vald;
    int vali;
    double rm;
    double roundd;
    int roundi;
    double workWith;
    double finalVal;
    public:
    Round(){}
    double runRound(double num){
        this->round(num);
        finalVal = ni+workWith;
        return finalVal;
    }

    double remInt(double num){
        nd = num;
        ni = nd;
        rem =  nd - ni;
        return rem;
    }

    double mul(double num, int i){
        vald = num * powbase(10,i);
        vali = vald;
        rm = vald - vali;
        if(rm>=0.5){
            vali++;
        }
        vald = vali;
        return vald/powbase(10,i);
    }
    float powbase(int base, int power){
        if(power==0){
            return 1;
        }
        if(power > 0){
            return base * powbase(base,power-1);
        }
        if(power<0)
        {
            return powbase(base,power+1)*1/base;
        }
        else{
            return 1;
        }
    }


    void round(double num){
        roundd = num*1000;
        roundi = roundd;
        
        roundd = roundi;
        roundd = roundd/1000;

        workWith = remInt(roundd);

        for(int i=2;i>1;i--){
            workWith = mul(workWith,i);
        }
    }
};

int adjust(double num,double mul){
    double valz = num*mul;
    int valx = valz;
    double remz = valz - valx;
    if(remz>0.5){
        valx++;
    }
    return valx;
}



int main(){
    double val;
    double valz;
    cin>>valz;
    val = valz;
    valz = 40/valz;
    Round round;
    double m = round.runRound(valz);
    cout<<m<<endl<<endl;
    for(int i=0; i<val; i++){
        cout<<adjust(i,m)<<endl;
    }
    return 0;
}