#include <iostream>
using namespace std;

class Polynomial
{
protected:
    int degree;
    int val;
    int *newarr = new int[degree + 1];
    int ymax, ymin, xmax, xmin, minx, miny, rangeX;
    int origin, accepted;

public:
    Polynomial() {}
    void Poly()
    {
        cout << "Input Polynomial degree:\n";
        cin >> degree;
        for (int i = degree; i >= 0; i--)
        {
            cout << "Input coefficient of x raised to power " << i << ":\n";
            cin >> val;
            newarr[i] = val;
        }
        for (int i = degree; i >= 0; i--)
        {
            cout << newarr[i] << " ";
        }
        cout << "\n";
    }
    void Xspace()
    {
        for (int x = 1; x <= 10 * minx; x++)
        {
            cout << "  ";
        }
    }
    void xvals()
    {
        cout << "Input range of X values\n"
        ;

        cout << "Xmin: ";
        cin >> xmin;

        cout << "Xmax: ";
        cin >> xmax;

        minx = -1 * xmin;
        rangeX = minx + xmax;
    }
};

class Plotting : public Polynomial
{
protected:
    int *arrj = new int[rangeX];
    int *arrk = new int[rangeX];
    int *arrsum = new int[2 * (rangeX + 1)];

public:
    Plotting()
    {
    }
    ~Plotting() {}
    float powbase(int base, int power)
    {
        if (power == 0)
        {
            return 1;
        }
        if (power > 0)
        {
            return base * powbase(base, power - 1);
        }
        if (power < 0)
        {
            return powbase(base, power + 1) * 1 / base;
        }
        else
        {
            return 1;
        }
    }

    void plot()
    {
        for (int j = xmin; j < 0; j++)
        {
            int sumj = 0;
            for (int i = degree; i >= 0; i--)
            {
                sumj += newarr[i] * this->powbase(j, i);
            }
            arrj[j + minx] = sumj;
        }
        for (int k = 0; k <= xmax; k++)
        {
            int sumk = 0;
            for (int i = degree; i >= 0; i--)
            {
                sumk += newarr[i] * this->powbase(k, i);
            }
            arrk[k] = sumk;
        }
        for (int index = 0; index < minx; index++)
        {
            arrsum[index] = arrj[index];
        }
        for (int index = 0; index <= xmax; index++)
        {
            arrsum[index + minx] = arrk[index];
        }
        cout << "\n";
    }

    int ymaxv()
    {
        int max = 0;
        for (int i = 0; i <= (minx + xmax); i++)
        {
            if (arrsum[i] >= max)
            {
                max = arrsum[i];
            }
        }
        double number = max;
        int integer = number;
        double decimal = number - integer;

        if (number >= 0)
        {
            if (decimal >= 0.5)
            {
                integer++;
            }
        }
        else if (number < 0)
        {
            if (decimal <= -0.5)
            {
                integer--;
            }
        }

        return integer;
    }

    int yminv()
    {
        int min = 0;
        for (int i = 0; i <= (minx + xmax); i++)
        {
            if (arrsum[i] <= min)
            {
                min = arrsum[i];
            }
        }
        double number = min;
        int integer = number;
        double decimal = number - integer;

        if (number >= 0)
        {
            if (decimal >= 0.5)
            {
                integer++;
            }
        }
        else if (number < 0)
        {
            if (decimal <= -0.5)
            {
                integer--;
            }
        }

        return integer;
    }

    void graphs()
    {
        ymin = this->yminv();
        ymax = this->ymaxv();

        miny = -1 * ymin;
    }

    int getxmax()
    {
        return xmax;
    }
    int getxmin()
    {
        return xmin;
    }

    void Ymaxline()
    {
        if ((minx + xmax) <= 15)
        {
            for (int i = 1; i <= 5 * ymax; i++)
            {
                Xspace();
                cout << "|" << "\n";
            }
        }
    }
    void Xline()
    {
        if ((minx + xmax) <= 15)
        {
            for (int a = 1; a <= 10 * minx; a++)
            {
                cout << "--";
            }
            cout << "|";
            for (int b = 1; b <= 10 * xmax; b++)
            {
                cout << "--";
            }
            cout << "\n";
        }
    }
    void Yminline()
    {
        if ((minx + xmax) <= 15)
        {
            for (int i = 1; i <= 5 * miny; i++)
            {
                Xspace();
                cout << "|" << "\n";
            }
        }
    }
};

class Combine : public Plotting
{
protected:
    double numVal = 40;
    double conversion = 0;
    int nums = 0;
    double *graphingArr = new double[2 * (rangeX + 1)];
    int sgn = 1;
    int ns, num;
    double rem;

public:
    Combine(){};
    void runCombine()
    { // Number should not be greater than 80,000,000 (Eighty Million).
        nums = miny + ymax;
        conversion = numVal / nums;
        // cout << "***" << conversion << "***\n";
        this->finalgraph();
    }

    int roundDown(double num)
    {
        int sgn = 1;
        if (num < 0)
        {
            num = -num;
            sgn = -sgn;
        }
        int ns = num;
        double rem = num - ns;

        if (rem >= 0.5)
        {
            ns++;
        }

        if (ns > numVal)
        {
            ns = numVal;
        }
        return ns * sgn;
    }

    void finalgraph()
    {
        for (int i = 0; i <= (minx + xmax); i++)
        {
            // graphingArr[i] = conversion * arrsum[i];
            // cout<<"When x is "<<i+xmin<<" y is "<<arrsum[i]<<" and "<<graphingArr[i]<<" in graph units and "<<this->roundDown(graphingArr[i])<<" when rounded down.\n";
            graphingArr[i] = this->roundDown((conversion * arrsum[i]));
            // cout << "When x is " << i + xmin << " y is " << arrsum[i] << " and " << graphingArr[i] << " in graphing units when rounded down.\n";
        }
    }
};

class FinalClass : public Combine
{
private:
    int graphymax;
    int graphymin;

public:
    FinalClass() {}
    ~FinalClass()
    {
        delete[] newarr;
        delete[] arrj;
        delete[] arrk;
        delete[] arrsum;
        delete[] graphingArr;
    }
    void runFinalClass()
    {
        cout<<"Input a number to select the corresponding option, each number provided below refers to the option in front of it.\n";
        int inputformat;
        cout << "Polynomial 1\n"
             << "Conic 2\n"
             << "exit 3\n";
        cin >> inputformat;
        if (inputformat == 1)
        {
            this->Poly();
            this->xvals();
            if (this->getxmin() <= 0 && this->getxmax() >= 0)
            {
            this->plot();
            this->graphs();
            this->runCombine();
            graphymax = graphmaxv();
            graphymin = graphminv();
            this->stateGraph();
            cout <<"\n"
                 << "Maximum Y value: "<<graphymax<<"\n"
                 << "Minimum Y value: "<<graphymin <<"\n";
                this->Ymaxline();
                this->Xline();
                this->Yminline();
            }
            else if (this->getxmin() > 0 && this->getxmax() >= 0)
            {
                cout << "Minimum value of x should be equal to or less than 0, but it is greater than 0.\n";
                cout<<"Program exited.";              
            }
            else if (this->getxmax() < 0 && this->getxmin() <= 0){
                cout << "Maximum value of x should be equal to or greater than 0, but it is less than 0.\n";  
                cout<<"Program exited.";              
            }
            else if (this->getxmin() > 0 && this->getxmax() < 0)
            {
                cout << "Maximum value of x should be equal to or greater than 0 and minimum value of x should be equal to or less than 0, but the maximum value is less than 0 and the minimum value is greater than 0\n";  
                cout<<"Program exited.";           
            }
        }
        else if (inputformat == 2)
        {
        }
        else if (inputformat == 3)
        {
            cout << "Program exited.";
        }
    }

    int graphmaxv()
    {
        int max = 0;
        for (int i = 0; i <= (minx + xmax); i++)
        {
            if (graphingArr[i] >= max)
            {
                max = graphingArr[i];
            }
        }
        double number = max;
        int integer = number;
        double decimal = number - integer;

        if (number >= 0)
        {
            if (decimal >= 0.5)
            {
                integer++;
            }
        }
        else if (number < 0)
        {
            if (decimal <= -0.5)
            {
                integer--;
            }
        }

        return integer;
    }

    int graphminv()
    {
        int min = 0;
        for (int i = 0; i <= (minx + xmax); i++)
        {
            if (graphingArr[i] <= min)
            {
                min = graphingArr[i];
            }
        }
        double number = min;
        int integer = number;
        double decimal = number - integer;

        if (number >= 0)
        {
            if (decimal >= 0.5)
            {
                integer++;
            }
        }
        else if (number < 0)
        {
            if (decimal <= -0.5)
            {
                integer--;
            }
        }

        return integer;
    }

    void ComplementYlines(int i){
        if (i >= 0)
        {
            if(graphingArr[minx-1]==i && graphingArr[minx]!=i){
                if (i >= 10)
                {
                    cout << "  * " << i << "-|  ";
                }
                else
                {
                    cout << "  *  " << i << "-|  ";
                }                    
            }
            else if(graphingArr[minx]==i && graphingArr[minx-1]!=i){
                if (i >= 10)
                {
                    cout << "    " << i << "-*  ";
                }
                else
                {
                    cout << "     " << i << "-*  ";
                }                    
            }
            else if(graphingArr[minx-1]==1 && graphingArr[minx]==i){
                if (i>=10)
                {
                    cout << "  * " << i << "-*  ";
                }
                else{
                    cout << "  *  " << i << "-*  ";
                }
            }
            else{
                if (i >= 10)
                {
                    cout << "    " << i << "-|  ";
                }
                else
                {
                    cout << "     " << i << "-|  ";
                }                   
            }
        }
        else
        {
            if(graphingArr[minx-1]==i && graphingArr[minx]!=i){
                if (i <= -10)
                {
                    cout << "  *" << i << "-|  ";
                }
                else
                {
                    cout << "  * " << i << "-|  ";
                }                    
            }
            else if(graphingArr[minx]==i && graphingArr[minx-1]!=i){
                if (i <= -10)
                {
                    cout << "   " << i << "-*  ";
                }
                else
                {
                    cout << "    " << i << "-*  ";
                }                    
            }
            else if(graphingArr[minx-1]==i && graphingArr[minx]==i){
                if (i <= -10)
                {
                    cout << "  *" << i << "-*  ";
                }
                else{
                    cout << "  * " << i << "-*  "; 
                }
            }
            else{
                if (i <= -10)
                {
                    cout << "   " << i << "-|  ";
                }
                else
                {
                    cout << "    " << i << "-|  ";
                }
            }
        }
    }

    void Ymaxline()
    {
        for (int i = graphymax; i > 0; i--)
        {
            for (int j=1; j<minx; j++)
            {
                if(graphingArr[j-1]==i)
                {
                    cout<<"  *  ";
                }
                else
                {
                    cout<<"     ";
                }
            }
            ComplementYlines(i);
            for(int j=1; j<=xmax;j++)
            {
                if(graphingArr[j+minx]==i){
                    cout<<"  *  ";
                }
                else
                {
                    cout<<"     ";
                }
            }
            cout<<"\n";
        }
    }
    void Yminline()
    {
        for (int i = -1; i >= graphymin; i--)
        {
            if (i == -1)
            {
                continue;
            }
            else
            {
                for (int j=1; j<minx; j++)
                {
                if(graphingArr[j-1]==i)
                {
                    cout<<"  *  ";
                }
                else
                {
                    cout<<"     ";
                }
                }
                ComplementYlines(i);
                for(int j=1; j<=xmax;j++)
                {
                    if(graphingArr[j+minx]==i){
                        cout<<"  *  ";
                    }
                    else
                    {
                        cout<<"     ";
                    }
                }                
            }
            cout<<"\n";
        }
    }

    void ComplementXline(int i){
        if ((i + xmin) < 0)
            {
                if ((i + xmin) <= -10)
                {
                    cout << " " << i + xmin << " ";
                }
                else
                {
                    if (graphymin < 0)
                    {
                        if ((i + xmin) == -1)
                        {
                            cout << " " << i + xmin << " ";
                        }
                        else
                        {
                            cout << " " << i + xmin << "  ";
                        }
                    }
                    else
                    {
                        cout << " " << i + xmin << "  ";
                    }                    
                }
            }
            if ((i + xmin) == 0)
            {
                if (graphymin < 0)
                {
                    if(minx==0){
                        cout<<"      |" << i + xmin <<" ";
                    }
                    else{
                        cout << "-1-|" << i + xmin << " ";
                    }
                }
                else
                {
                    if(minx == 0){
                        cout << "       " << i + xmin<<"  ";
                    }
                    else{
                        cout << "  " << i + xmin << "  ";
                    }
                }
            }
            else if ((i + xmin) > 0)
            {
                if ((i + xmin) >= 10)
                {
                    cout << "  " << i + xmin << " ";
                }
                else
                {
                    cout << "  " << i + xmin << "  ";
                }
            }
    }
    void Xline()
    {
        for (int i = 0; i <= (minx + xmax); i++)
        {
            if(graphingArr[i]==0){
                if(minx==0){
                    cout<<"     --*--";
                }
                else{
                    cout<< "--*--";
                }
            }
            else{
                if ((i + xmin) == 0)
                {
                    if(minx==0){
                        cout<<"     --|--";
                    }
                    else{
                        cout << "--|--";
                    }
                }
                else
                {
                    cout << "--:--";
                }
            }
        }
        cout << "\n";
        for (int i = 0; i <= (minx + xmax); i++)
        {
            if(graphingArr[i]==-1){
                cout << "  * ";
            }
            else{
                ComplementXline(i);
            }
        }
        cout << "\n";
    }
    void stateGraph(){
        cout<<"Graph of y =";
        for(int i=degree; i>=0; i--){
            int store = 0;

            if(i==degree){
                if(newarr[i]==0){
                    cout<<" 0";
                }
                else if(newarr[i]==-1)
                {
                    if(i==1){
                        cout<<" -x";
                    }
                    else{
                        cout<<" -x^"<<i;
                    } 
                }
                else if(newarr[i]==1)
                {
                    if(i==1){
                        cout<<" x";
                    }
                    else{
                        cout<<" x^"<<i;
                    }
                }
                else{
                    if(i==1){
                        cout<<" "<<newarr[i]<<"x";
                    }
                    else{
                        cout<<" "<<newarr[i]<<"x^"<<i;
                    }
                }                
            }
            else
            {                
                if(newarr[i]==0){
                    cout<<" + 0";
                }
                else if(newarr[i]==-1){
                    if(i==0){
                        cout<<" - 1";
                    }
                    if(i==1){
                        cout<<" - x";
                    }
                    else{
                        cout<<" - x^"<<i;
                    }
                }
                else if(newarr[i]==1){
                    if(i==0){
                        cout<<" + 1";
                    }
                    else if(i==1){
                        cout<<" + x";
                    }
                    else{
                        cout<<" + x^"<<i;
                    }
                }
                else if(newarr[i]>1){
                    if(i==0){
                        cout<<" + "<<newarr[i];
                    }
                    else if(i==1){
                        cout<<" + "<<newarr[i]<<"x";
                    }
                    else{
                        cout<<" + "<<newarr[i]<<"x^"<<i;
                    }
                }
                else if(newarr[i]<-1){
                    store = -newarr[i];
                    if(i==0){
                        cout<<" - "<<store;
                    }
                    else if(i==1){
                        cout<<" - "<<store<<"x";
                    }
                    else{
                        cout<<" - "<<store<<"x^"<<i;
                    }
                }
            }
        }
        cout<<" in the interval "<<xmin<<" <= x <= "<<xmax<<".";
    }
};
int main()
{
    FinalClass final;
    final.runFinalClass();
    return 0;
}