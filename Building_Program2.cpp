//Program 2 : Calculate the surface of the building exposed to sunlight

#include <bits/stdc++.h>
using namespace std;

struct point{   //Coordinates
    double x,y;
};

struct building{
   struct point p1,p2,p3,p4;

   float s1,s2,s3;
   void calwall(){   // Calculates the length of the 3 walls that will be affected by the sunlight
         s1=sqrt(pow(p1.x - p2.x, 2)+ pow(p1.y - p2.y, 2) * 1.0);   // left wall length
         s2=sqrt(pow(p2.x - p3.x, 2)+ pow(p2.y - p2.y, 2) * 1.0);   // upper terrace length
         s3=sqrt(pow(p3.x - p4.x, 2)+ pow(p3.y - p4.y, 2) * 1.0);   // right wall length
   }
};

double slope(double x1, double y1, double x2, double y2){   // Calculates the slope of the line
    return (y2 - y1) / (x2 - x1);
}

int main(){
    building b[] = { { {4,0},{4,-5},{7,-5},{7,0} }, { {0.4,-2},{0.4,-5},{2.5,-5},{2.5,-2} } };      //For Case 1 involving 1 building, output will be 8.
                                                                                                    //This is the input for Case 2, and same goes for the point
    int s= sizeof b/sizeof b[0];    //Number of buildings
    for(int i=0;i<s;i++){
       b[i].calwall();  //Calculates lengths of all the walls of each building
    }
    point sun = {-3.5,1};   //Sun coordinates  //Case-2 points

    int maxh = INT_MIN;  //Max height of building

    double light=b[0].s1+b[0].s2; // since light of sun will always fall on the first building

    maxh=b[0].s1;   //max height = height of new building
    double maxx=b[0].p3.x;
    double maxy=b[0].p3.y;

    for(int i =1;i<s;i++){
     if(maxh<=b[i-1].s1){   //if building is larger than previously large building

        maxh=b[i-1].s1;     // New max height of building
        double slo=slope(sun.x,sun.y,maxx,maxy); // Calculates the slope of ray of light

        double newp= (slo * (b[i].p1.x - sun.x) )+sun.y; //Calculates the y coordinate where the sunlight will strike

        float dist =sqrt(pow(b[i].p3.y - newp, 2) * 1.0);

        light=light+b[i].s2+ dist;

        double maxx=b[0].p3.x;// new max x
        double maxy=b[0].p3.y; // new max y
        }
    }
  cout<<"Output Length of Surface Exposed exposed to sunlight = ";
  cout<<light<<endl;    //Final Output
}
