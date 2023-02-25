#include <iostream>
#include <ctime>
using namespace std;


class Factors{
    private:
    int check;
    double lastArrVal = 0;
    int dividend = 2;
    int resulting;
    int index = 0;
    int lastVal, checkLast;
    int globalIndex = 0;
    protected:
    double * newarr = new double[100];
    int newarrlen = 0;
    public:
    Factors(){}
    void runFactors(double num){
        if(num<0){
            num = -num;
            cout<<"-"<<num<<" converted to "<<num<<" for easy computation."<<endl;
        }
        if(num==0 || num==1){
            newarr[index] = num;
        }
        else{
            check = this->prime(num);
            if(check == 1){
            newarr[globalIndex] = 1;
            globalIndex++;
            newarr[globalIndex] = num;
        }
            else{
                manage(num);
            }
        }

        newarrlen = globalIndex;
        globalIndex = 0;
    }
    void manage(double num){
        lastVal = process(num);
        checkLast = this->prime(lastVal);
        // cout<<lastVal<<" . "<<checkLast<<endl;
        if(lastVal>1){
            while(checkLast==0){
                lastVal = process(lastVal);
                checkLast = this->prime(lastVal);
                // cout<<lastVal<<" . "<<checkLast<<endl;
            };
        }
    }
    int process(double num){
        int * specarr = new int[100];

        resulting = num;
        int res;

        while(resulting>1){
            specarr[0] = 1;
            res = divide(resulting, &dividend,specarr);
            resulting = res;
        }
        if(lastArrVal>1){
            index++;
            specarr[index] = lastArrVal;
        }


        for(int x = 0; x <= index; x++){
            newarr[x+globalIndex] = specarr[x];
        }
        globalIndex += index;
        index = 0;
        return lastArrVal;
    }
    int divide(double value, int * dividendPtr,int spec[]){
        double result,resultRem;
        int resultInt;
        int returnvalue = 0;
        result = value/ *dividendPtr;
        resultInt = result;
        resultRem = result-resultInt;
        if(resultRem>0){
        int store = *dividendPtr;
        store++;
        dividendPtr = &store;
        divide(value, dividendPtr,spec);
        }else if(resultRem==0){
            index++;
            spec[index] = *dividendPtr;
            lastArrVal = resultInt;
            returnvalue = resultInt;
        }
        return returnvalue;
    }

    void removeRep(){
        for(int x = 1; x<=globalIndex; x++){//Works only if 1 is not repeated from the second index upwards.
            if(newarr[x] == 1){
                for(int a = x; a<=globalIndex; a++){
                    newarr[a] = newarr[a+1];
                }
                globalIndex--;
            }
        }
    }

    void print(){
        for(int i = 0; i<=globalIndex; i++){
            cout<<" --"<<newarr[i]<<endl;
        }
        cout<<"..."<<globalIndex<<endl;
    }

    void printAsFactors(double number){
        this->removeRep();
        cout<<number<<": ";
        int sum = 0;
        if(globalIndex == 0){
            cout<<newarr[globalIndex]<<endl;
        }
        else{
            for(int i = 0; i<=globalIndex; i++){
                if(i==globalIndex){
                    cout<<newarr[i];
                }
                else{
                    cout<<newarr[i]<<"x";
                }
                sum+=newarr[i];
            }
            cout<<" -> "<<sum;
            sum = 0;
        }
    }


    int getArrLen(){
        this->removeRep();
        return globalIndex+1;
    }


    int prime(double number){
    int returnvalue = 0;
    for(double i = 2; i<=number; i++){
        double numvalue = number/i;
        int numV = numvalue;
        double numVrem = numvalue - numV;
        if(numVrem == 0){
            if(i == number){
                // cout<<"Is Prime";
                returnvalue = 1;
            }else{
                // cout<<"Is not Prime";
                returnvalue = 0;
            }
            break;
        }
    }
    return returnvalue;
    }
};

class AscendingFactors : public Factors {
    private:
    double inc = 1;
    int index = 0;
    double first = 0;
    double second = 0;
    int id = 0;
    int occurence = 0;
    int returnValue = 0;
    int val = 0;
    int iVal = 0;
    int parVal = 0;
    int swap = 0;
    double interval;
    double takein = 0;
    double coeff1 = 0;// represents n / numval
    double coeff2 = 0;// represents n / product of intervalArray elements [0] and [1](highest integer in graph)
    double product = 0;
    double * desiredArr = new double [2];
    double * intervalArr = new double [2];
    double * takeArr = new double[2];
    double desIndex = 0;
    double t = 0;
    double min = 0;
    int range = 0;
    protected:
    double numVal = 40;
    int len = 0;
    double showNum = 0;
    double showProduct = 0;
    double *showDesiredArr = new double[10];
    double *showIntervalArr = new double[10];
    double *showTakeArr = new double[10];
    double convFactor = 0;
    public:

    AscendingFactors(){}
    void changeNumVal(double n){
        numVal = n;
    }
    void outputAscFactors(double n){
        range = modulo5(n)+1;
        t = prime(n);
        if(t == 1){
            min = this->runAscFactors(n+1);
        }
        else{
            min = this->runAscFactors(n);
        }

            clearValues();
            double hold;
            for(int i=1; i<range; i++){
                t = prime(n+i);
                if(t == 0){
                    hold = this->runAscFactors(n+i);
                    clearValues();
                    if(min>hold){
                        min = hold;
                        desIndex = i;
                    }
                }
            }
        clearValues();

        this->runAscFactors(n+desIndex);
        convFactor = product/(n+desIndex);
        showNum = n;
        showProduct = product;

        if(showProduct<=numVal){
            // IMPORTANT VALUES FOR COUT: N, PRODUCT, DESIREDARR, INTERVALARR,TAKEARR AND INTERVAL.
            cout<<"Number entered is "<<n<<", Value of Number entered in Graph units is "<<n*convFactor<<", Conversion Factor is "<<convFactor<<endl;
            cout<<"Number used is "<<n+desIndex<<", Graph max value is "<<product<<", ";

            for(int j=0; j<2; j++){
                cout<<"Num factor "<<j+1<<": "<<desiredArr[j]<<", ";
            }

            for(int j=0; j<2; j++){
                cout<<"Graph factor "<<j+1<<": "<<intervalArr[j]<<", ";
            }

            for(int j=0; j<2; j++){
                cout<<"TA"<<j+1<<": "<<takeArr[j]<<", ";
            }
            cout<<"Interval: "<<interval<<"."<<endl;
            cout<<"Minimum Value: "<<min<<" "<<"Desired Index: "<<desIndex<<endl<<endl;
        }
        clearValues();
    };
    double runAscFactors(double n){
        this->runFactors(n);
        parVal = n;
        len = newarrlen;
        int store = 2*(len*len);
        double *arrstore = new double[store];
        double * modifiedarrstore = new double[store];
        double* sumarr = new double[store];
        this->solve(n, newarr, len, arrstore, modifiedarrstore, sumarr);

        // for(int a = 0; a<2*index; a++){
        //     cout<<arrstore[a]<<"* ";
        // }

        // cout<<endl;

        // for(int a = 0; a<2*id; a++){
        //     cout<<modifiedarrstore[a]<<"** ";
        // }

        // cout<<endl;

        for(int i = 0; i<id; i++){
            val = modifiedarrstore[(2*i)+1] - modifiedarrstore[(2*i)];
            if(val<0){
                val = -val;
            }
            if(val<=parVal){
                parVal = val;
                iVal = i;
                
            }
        }
        desiredArr[0] = modifiedarrstore[(2*iVal)];
        desiredArr[1] = modifiedarrstore[(2*iVal)+1];
        if(desiredArr[0]<desiredArr[1]){
            swap = desiredArr[1];
            desiredArr[1] = desiredArr[0];
            desiredArr[0] = swap;
        }

        interval = desiredArr[1];

        intArr(intervalArr, n, desiredArr,  &interval, takeArr);

        if(interval == 0){
            interval = numVal/intervalArr[0];
            interval = evalNum(interval);
            intervalArr[1] = interval;     
            product = desiredArr[0] * interval;
            double P = intervalArr[0] * intervalArr[1];
            coeff2 = n / P;
            takeArr[1] = coeff2;
        }

        //returnValue..
        double returnValue;
        if(takeArr[1]>=takeArr[0]){
            returnValue = takeArr[1] - takeArr[0];
        }
        else{
            returnValue = takeArr[0] - takeArr[1];
        }
        return returnValue;
    }

    double evalNum(double num){
        takein = num*10;
        int integerPart = takein;
        if(takein<1){
            evalNum(takein);
        }
        else{
            double remPart = takein-integerPart;
            if(remPart>=0.5){
                integerPart++;
            }
        takein = integerPart;
        takein /= 10;
        }
        return takein;
    }

    int modulo5(double n){
        double numd = n/5;
        int numi = numd;
        double rem = numd - numi;
        if(rem>0){
            numi++;
        }
        numi = numi*5 - n;
        return numi;
    }


    void solve(double n, double a[],double len, double arrstore[], double modifiedarrstore[], double sumarr[]){
        for(int i=0; i<len; i++){
            for(int x = i; x<len; x++){
                if(arrstore[2*(index-1)] == arrstore[(2*(index-1))+1]){
                    break;
                }
                first = a[x]*inc;
                inc = first;
                second = n/first;
                arrstore[2*index] = first;
                arrstore[(2*index)+1] = second;
                index++;

                if(this->duplicateCheck(arrstore,index,first,second, sumarr) == 0){
                    modifiedarrstore[(2*id)] = first;
                    modifiedarrstore[(2*id)+1] = second;
                    id++;
                }
            }
            inc = 1;
        }
    }

    int duplicateCheck(double arr[],int len,double first, double second, double sumarr[]){
        for(int i=0; i<len; i++){
            sumarr[i] = arr[(2*i)] + arr[(2*i)+1];
            if((first+second) == sumarr[i]){
                occurence++;
            }
        }
        if(occurence>1){
            returnValue = 1;
        }
        else{
            returnValue = 0;
        }
        occurence = 0;
        return returnValue;
    }
    
    void intArr(double intArr[],double n, double desArr[], double * intervalP, double * takeArr){
        product = desArr[0] * desArr[1];
        while(product>numVal){
            *intervalP -= 1;
            product = desArr[0] * *intervalP;
        }
        intArr[0] = desArr[0];
        intArr[1] = *intervalP;
        double P = intArr[0] * intArr[1];
        coeff1 = n / numVal;
        coeff2 = n / P;
        takeArr[0] = coeff1;
        takeArr[1] = coeff2;
    }

    void clearValues(){
        //Reset Values...
        inc = 1;
        index = 0;
        first = 0;
        second = 0;
        id = 0;
        occurence = 0;
        returnValue = 0;
        val = 0;
        iVal = 0;
        parVal = 0;
        swap = 0;
        interval;
        numVal = 40,takein = 0;
        coeff1 = 0;// represents n / numval
        coeff2 = 0;// represents n / product of intervalArray elements [0] and [1](highest integer in graph)
        product = 0;
        takeArr[0] = 0;
        takeArr[1] = 0;
    }
};

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

class Combine: public AscendingFactors, public Round{
    private:
    double valz = 1;
    double valy = 0;
    double output = 0;
    double conversion;
    public:
    Combine(){};
    void runCombine(double num){//Number should not be greater than 80,000,000 (Eighty Million).
        if(num<=numVal){
            valz = numVal/num;
            output = this->runRound(valz);
            valy = this->adjust(num,output);
            cout<<output<<endl;
            for(int i=0; i<=num; i++){
                cout<<adjust(i,output)<<" ";
            }
            conversion = output;
            cout<<endl;
        }
        else{
            this->outputAscFactors(num);
            convFactor = this->runRound(convFactor);
            for(int i=0; i<=num; i++){
                cout<<adjust(i,convFactor)<<" ";
            }
            conversion = convFactor;
            if(showProduct>numVal){
                valz = num/numVal;
                output = this->runRound(valz);
                cout<<output<<endl;
                for(int i=0; i<=numVal; i++){
                    cout<<adjust(i,output)<<" ";
                }
                cout<<endl;
                conversion = 1/output;
                // conversion = this->runRound(conversion);
            }
        }
        cout<<"***"<<conversion<<"***";
    }

    int adjust(double num,double mul){
        double valz = num*mul;
        int valx = valz;
        double remz = valz - valx;
        if(remz>0.5){
            valx++;
        }
    return valx;
    }
};

int main(){
    double par;
    cin>>par;
    Combine comb;
    comb.runCombine(par);
    // double value;
    // double prev, now, val;
    // prev = time(0);
    // for(int  i = 41; i <= 600; i++){
    //     AscendingFactors asc(i);
    // }

    // now = time(0);
    // val = now-prev;
    // if(val==1){
    //     cout<<"Loop took "<<val<<" second to run.";
    // }
    // else{
    //     cout<<"Loop took "<<val<<" seconds to run.";
    // }
    return 0;
}