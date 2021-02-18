#include <iostream>
#include <string>

double match=1.0;
//double mismatch=-1.0;
double mismatch=-0.2;

double returnscore(char num, char num2){ //returns 1.0 if inputs match and -0.2 if they dont match
    if(num==num2){
        return match;
    }
    else{
        return mismatch;
    }
}

double returnmaxscore(double n, double n2, double n3){ //returns the max of three inputs
    if((n>=n2) && (n>=n3)){
        return n;
    }
    if(n2>=n && n2>=n3){
        return n2;
    }
    else{
        return n3;
    }
}

double returnsimscore(std::string a, std::string b){ //

    int max;
    double total=0;

    if(a.length()>b.length()){
        max=a.length();}

    else{
        max=b.length();}

    for(int i=0;i<max;i++){
        if(a[i]==b[i]){
            total=total+1;
        }
        else if( (a[i]== '-') || (b[i]=='-') ){
            total=total-0.2;
        }
        else{
            total=total-0.15;
        }


    }
    return total;
}

void align(std::string x, std::string y){

    int xlen = x.length()+1;
    int ylen = y.length()+1;

    double scoresarray [xlen][ylen];

    for(int i=0; i<xlen; i++){ //Fills in all first row since we know all will be mismatch
        scoresarray[i][0] = (mismatch*i);
    }

    for(int j=0; j<ylen; j++){ //Fills in all first column
        scoresarray[0][j] = (mismatch*j);
    }

    for(int i=1; i<xlen; i++){ //fills in the rest of the array
        for(int k=1; k<ylen; k++){
            //scoresarray[i][k] = 1.1;
            double match = scoresarray[i-1][k-1] + returnscore(x[i-1], y[k-1]);
            double deletion = scoresarray[i-1][k] + mismatch;
            double insertion = scoresarray[i][k-1] + mismatch;
            scoresarray[i][k] = returnmaxscore(match, deletion, insertion);
           //double max = std::max(match, std::max(deletion, insertion));
           //scoresarray[i][k] = max;
        }
    }

        //Print Array
        std::cout << std::endl << "Score Array: " << std::endl;
        std::cout << std::endl;

        for(int i=0; i<xlen; i++){
            for(int j=0; j<ylen; j++) {

                std::cout <<scoresarray[i][j] << " ";
            }
            std::cout << std::endl;
        }
        int tempx=x.length();
        int tempy=y.length();

       std::string finalx="";
       std::string finaly="";

        while(tempx>0 || tempy>0){ //aligning strings into the finalx and finaly strings

            if( (tempx>0 && tempy>0) && x[tempx-1]==y[tempy-1] ){ //matching characters
                finalx=x[tempx-1]+finalx;
                finaly=y[tempy-1]+finaly;
                --tempx;
                --tempy;
            }

            else if( tempx>0 && scoresarray[tempx][tempy]==(scoresarray[tempx-1][tempy] + mismatch)){
                finalx = x[tempx-1]+finalx;
                finaly = "-" + finaly;
                --tempx;
            }

            else{
                finalx = "-" + finalx;
                finaly = y[tempy-1] + finaly;
                --tempy;
            }
        }

        std::cout<<std::endl<<"Aligned strings are: " << std::endl;
        std::cout<<finalx<<std::endl;
        std::cout<<finaly<<std::endl;

        double endscore = returnsimscore(finalx, finaly);
        std::cout<<"And so the similarity score is: " <<  endscore << std::endl;



}

int main() {

    std::string xprob = "GTGAACGCTGGCGGCGTGCT";
    std::string yprob = "AGCTAATACCCCATACGTTC";

    std::string x = xprob;
    std::string y = yprob;

    std::string tests = "crust";
    std::string tests2 = "trust";
    std::cout<<"Testing return score function"<<std::endl;
    double test = returnscore(tests[4], tests2[4]);
    std::cout<<"Should be a match and print 1.0: " << test<<std::endl;

    double test2 = returnscore(tests[0], tests2[0]);
    std::cout<<"Should be a mismatch and print -0.2: "<< test2<<std::endl;

    std::cout<<std::endl<<"Testing my max function"<<std::endl;
    double ex=-552.0;
    double ex2=20.2;
    double ex3=20.2;
    double max=0;
    max= returnmaxscore(ex, ex2, ex3);
    std::cout<<"Should be max 20.2: " << max << std::endl;

    ex=-552.0;
    ex2=-20.2;
    ex3=0;
    max=0;
    max= returnmaxscore(ex, ex2, ex3);
    std::cout<<"Should be max 0: " << max << std::endl;

    std::cout<<std::endl<<"Testing my similarity score function"<<std::endl;

    std::string str ="hello";
    std::string str2 = "hello";
    double score = returnsimscore(str, str2);
    std::cout<<"Should be 5: "<<score<<std::endl;

    std::string str3 ="hello";
    std::string str4 = "tel-o";
    score = returnsimscore(str3, str4);
    std::cout<<"Should be 2.65: "<<score<<std::endl;

    std::string str5 ="g";
    std::string str6 = "-";
    score = returnsimscore(str5, str6);
    std::cout<<"Should be -0.2: "<<score<<std::endl;

    std::string str7 ="six";
    std::string str8 = "bag";
    score = returnsimscore(str7, str8);
    std::cout<<"Should be -0.45: "<<score<<std::endl;

    align(x, y);



    return 0;
}