#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<time.h>
#define A 6
#define INT_MAX 9999

int ary[6][6] = {
                  {0,253,295,287,330,135} ,
                  {257,0,219,40,282,111} ,
                  {296,219,0,250,64,184} ,
                  {289,40,249,0,312,149},
                  {331,283,64,314,0,239},
                  {136,111,175,152,238,0}
                };
int n = 6, cost = 0;
int start;
char tspRoute[400];
char routef[200];
int choice;
double total_time;

void Calculate_Cost(int value, int choice){
float cost;
if(choice==1){
cost= (value*1.08);
}
else if(choice==2){
cost= (value*1.188);
}
else if(choice==3){
cost= (value*1.35);
}
else if(choice==4){
cost= (value*1.836);
}
else if(choice==5){
cost= (value*2.036);
}
cost = floor(100*cost)/100;
printf("The expense required to travel from the selected source to the destination is Rs.%0.2f\n",cost);
}


void write_tsp()
{
FILE* fptr;
fptr = fopen("tsp_route.txt", "a");
if (fptr == NULL)
printf("\nError");
strcat(tspRoute, "\n");
fprintf(fptr, "%s", tspRoute);
fclose(fptr);
}
int least(int c,int *completed)
{
int i, nc = 9999;
int min = 9999, kmin;

for (i = 0; i < n; i++)
{
if ((ary[c][i] != start) && (completed[i] == 0))
if (ary[c][i] + ary[i][c] < min)
{
min = ary[i][start] + ary[c][i];
kmin = ary[c][i];
nc = i;
}
}

if (min != 9999)
cost += kmin;

return nc;
}
//int ctrtsp = 0;
void mincost(int city, int *completed)
{
char names[6][100] = { {"Delhi"},{"Dehradun"},{"Ramnagar"},{"Mussorie"},{"Nanital"},{"Muzaffarnagar"} };
int i, ncity;
completed[city] = 1;
// if (ctrtsp == 0)
// {
// strcat(tspRoute, names[city]);
// strcat(tspRoute, " ");
// ctrtsp = 1;
// }

printf("%s--->", names[city]);
strcat(tspRoute, names[city]);
strcat(tspRoute, "-->");
ncity = least(city,completed);

if (ncity == 9999)
{
ncity = start;
printf("%s", names[ncity]);
strcat(tspRoute, names[ncity]);
cost += ary[city][ncity];

return;
}
mincost(ncity,completed);
}

int isSubstring(char s1[50], char s2[100])
{
int M, N;
for (M = 0; s1[M] != '\0'; ++M);
for (N = 0; s2[N] != '\0'; ++N);


int i;
for (i = 0; i <= N - M; i++) {
int j;


for (j = 0; j < M; j++)
if (s2[i + j] != s1[j])
break;

if (j == M)
return i;
}

return -1;
}




bool read_tsp(char *srca)
{
FILE* fptr;
fptr = fopen("tsp_route.txt", "r");
if (fptr == NULL)
{
printf("error");
return false;
}
strcat(srca, " ");
char chunk[250];
int flag = 0;
while (fgets(chunk, sizeof(chunk), fptr) != NULL)
{
int res = isSubstring(srca, chunk);
if (res != -1)
{
fputs(chunk,stdout);
flag = 1;
break;
}
}
int i=0;
char temp;
int space=0;
if (flag == 0)
{
return false;
}
else if(flag==1)
{
char cost_c[4]="";
int i=0,pos=0,tempspace=0;
for(i=0; i<strlen(chunk); i++)
{
char chtemp=chunk[i];
if(chtemp==' ')
tempspace++;
if(tempspace==2)
{
int j;
int k=0;
for(j=i+1; j<strlen(chunk); j++)
{
cost_c[k]=chunk[j];
k++;
// printf("%c",cost_c[j]);
}
int cc = atoi(cost_c);
printf("\t\tThe minimum distance for the above route is %d.(from the file)",cc);
printf("\n\t\t");
Calculate_Cost(cc,choice);
break;
}
}
return true;
}
}

void read_route(char src[50], char dest[50])
{
FILE* fptr;
fptr = fopen("minor_route.txt", "r");
if (fptr == NULL)
{
printf("error");
}
char chunk[200];
char name[100] = "";
strcat(name, src);
strcat(name, ":");
strcat(name, dest);
int flag = 0;
while (fgets(chunk, sizeof(chunk), fptr) != NULL)
{
int res = isSubstring(name, chunk);
if (res != -1)
{
fputs(chunk, stdout);
printf("\t\t(from the file)");
flag = 1;
break;
}
}
}

void write_route(char route[200])
{
FILE* fptr;
fptr = fopen("minor_route.txt", "a");
if (fptr == NULL)
printf("\nError");
strcat(route, "\n");
fprintf(fptr, "%s", route);
fclose(fptr);
}

bool read_file(char src[40], char dest[40]) {
FILE* fptr;
fptr = fopen("minor.txt", "r");
if (fptr == NULL)
{
printf("error");
return false;
}
char chunk[100];
char name[200] = "";
strcat(name, src);
strcat(name, " ");
strcat(name, dest);
int flag = 0;
while (fgets(chunk, sizeof(chunk), fptr) != NULL)
{
int res = isSubstring(name, chunk);
//int res1 = isSubstring(dest,chunk);
if (res != -1)
{
flag = 1;
break;
}
}
if (flag == 0)
return false;
else
{
char cost_c[4];
int i=0,pos=0,tempspace=0;
for(i=0; i<strlen(chunk); i++)
{
char chtemp=chunk[i];
if(chtemp==' ')
tempspace++;
if(tempspace==2)
{
int j;
int k=0;
for(j=i+1; j<strlen(chunk); j++)
{
cost_c[k]=chunk[j];
k++;
// printf("%c",cost_c[j]);
}
int cc = atoi(cost_c);
// printf("%d",cc);
printf("\n\t\tThe minimum distance between the %s and %s is %d units.(from the file)\n\t\t",src,dest,cc);
read_route(src, dest);
printf("\n\t\t");
Calculate_Cost(cc,choice);
break;
}
}
return true;
}
}

void write_file(char src[100], char dest[40], int res)
{
FILE* fptr;
fptr = fopen("minor.txt", "a");
if (fptr == NULL)
printf("\nError");
char result[10];
strcat(src, " ");
strcat(src, dest);
strcat(src, " ");
sprintf(result, "%d", res);
strcat(src, result);
strcat(src, "\n");
fprintf(fptr, "%s", src);
fclose(fptr);
}

int minimum(int a, int b)
{
if (a < b)
return a;
else
return b;
}

int minDistance(int dist[], bool sptSet[])
{
int v, i;
int min = INT_MAX, min_index;
for (v = 0; v < A; v++)
if (sptSet[v] == false && dist[v] <= min)
min = dist[v], min_index = v;
return min_index;
}

int dijkstra(int G[A][A], int n, int startnode, int destination,int choice, int flag)
{
int value;
char names[6][100] = { {"Delhi"},{"Dehradun"},{"Ramnagar"},{"Mussorie"},{"Nanital"},{"Muzaffarnagar"} };
char route[200];
strcat(route, "");
strcat(route, names[startnode]);
strcat(route, ":");
strcat(route, names[destination]);
strcat(route, " ");
int cost[A][A], distance[A], pred[A];
int visited[A], count, mindistance, nextnode, i, j;

//pred[] stores the predecessor of each node
//count gives the number of nodes seen so far
//create the cost matrix
for (i = 0; i < n; i++)
for (j = 0; j < n; j++)
if (G[i][j] == 0)
cost[i][j] = INT_MAX;
else
cost[i][j] = G[i][j];

//initialize pred[],distance[] and visited[]
for (i = 0; i < n; i++)
{
distance[i] = cost[startnode][i];
pred[i] = startnode;
visited[i] = 0;
}

distance[startnode] = 0;
visited[startnode] = 1;
count = 1;

while (count < n - 1)
{
mindistance = INT_MAX;

//nextnode gives the node at minimum distance
for (i = 0; i < n; i++)
if (distance[i] < mindistance && !visited[i])
{
mindistance = distance[i];
nextnode = i;
}

//check if a better path exists through nextnode            
visited[nextnode] = 1;
for (i = 0; i < n; i++)
if (!visited[i])
if (mindistance + cost[nextnode][i] < distance[i])
{
distance[i] = mindistance + cost[nextnode][i];
pred[i] = nextnode;
}
count++;
}

//print the path and distance of each node
for (i = 0; i < n; i++)
if (i != startnode && i == destination)
{
value=distance[i];
printf("\n\t\tDistance between the entered Source And Destination=%d", distance[i]);
if (i == 0)
{
printf("\n\t\tPath=Delhi");
strcat(route, "Path=Delhi");
}
else if (i == 1)
{
printf("\n\t\tPath=Dehradun");
strcat(route, "Path=Dehradun");
}
else if (i == 2)
{
printf("\n\t\tPath=Ramnagar");
strcat(route, "Path=Ramnagar");
}
else if (i == 3)
{
printf("\n\t\tPath=Mussorie");
strcat(route, "Path=Mussorie");
}
else if (i == 4)
{
printf("\n\t\tPath=Nanital");
strcat(route, "Path=Nanital");
}
else if (i == 5)
{
printf("\n\t\tPath=Muzaffarnagar");
strcat(route, "Path=Muzaffarnagar");
}

j = i;
do
{
j = pred[j];
if (j == 0)
{
printf("<-Delhi");
strcat(route, "<-Delhi");
}
else if (j == 1)
{
printf("<-Dehradun");
strcat(route, "<-Dehradun");
}
else if (j == 2)
{
printf("<-Ramnagar");
strcat(route, "<-Ramnagar");
}
else if (j == 3)
{
printf("<-Mussorie");
strcat(route, "<-Mussorie");
}
if (j == 4)
{
printf("<-Nanital");
strcat(route, "<-Nanital");
}
if (j == 5)
{
printf("<-Muzaffarnagar");
strcat(route, "<-Muzaffarnagar");
}
}
while (j != startnode);
printf("\n\t\t");
Calculate_Cost(value,choice);
}
for (i = 0; i < n; i++)
if (i != startnode && i == destination)
{
if(flag!=1)
{
write_route(route);
}
return distance[i];
}
puts(route);
}

void printSolution(int path[A][A], int v, int u)
{
if (path[v][u] == v)
return;
printSolution(path, v, path[v][u]);

if (path[v][u] == 0)
{
printf("-Delhi-");
strcat(routef, "-Delhi-");
}
if (path[v][u] == 1)
{
printf("-Dehradun-");
strcat(routef, "-Dehradun-");
}
if (path[v][u] == 2)
{
printf("-Ramnagar-");
strcat(routef, "-Ramnagar--");
}
if (path[v][u] == 3)
{
printf("-Mussorie-");
strcat(routef, "-Mussorie--");
}
if (path[v][u] == 4)
{
printf("-Nanital-");
strcat(routef, "-Nanital-");
}
if (path[v][u] == 5)
{
printf("-Muzaffarnagar-");
strcat(routef, "-Muzaffarnagar-");
}
}
int ctrf = 0;

int helper_FLOYD(int s, int d, int dist[A][A], int N, int flag) {
char names[6][100] = { {"Delhi"},{"Dehradun"},{"Ramnagar"},{"Mussorie"},{"Nanital"},{"Muzaffarnagar"} };
//if (ctrf == 0)
//{
//char *temp="";
//strcpy(routef,temp);
//strcat(routef, "");
//strcat(routef, names[s]);
//strcat(routef, ":");
//strcat(routef, names[d]);
//strcat(routef, " ");
//ctrf++;
//}
int u, v, k, cost[N][N], path[N][N];

for (v = 0; v < N; v++)
{
for (u = 0; u < N; u++)
{
cost[v][u] = dist[v][u];

if (v == u)
path[v][u] = 0;
else if (cost[v][u] != INT_MAX)
path[v][u] = v;
else
path[v][u] = -1;
}
}
for (k = 0; k < N; k++)
{
for (v = 0; v < N; v++)
{
for (u = 0; u < N; u++)
{
if (cost[v][k] != INT_MAX && cost[k][u] != INT_MAX
&& cost[v][k] + cost[k][u] < cost[v][u])
{
cost[v][u] = cost[v][k] + cost[k][u];
path[v][u] = path[k][u];
}
}
}
}
int ans = cost[s][d];
    if(s==0)
    {
        printf("Delhi-");
        strcat(routef,"Delhi-");
    }
    if(s==1)
    {
        printf("Dehradun-");
        strcat(routef,"Dehradun-");
    }

    if(s==2)
    {
        printf("Ramnagar-");
        strcat(routef,"Ramnagar-");
    }
    if(s==3)
    {
        printf("Mussorie-");
        strcat(routef,"Mussorie-");
    }
    if(s==4)
    {
        printf("Nanital-");
        strcat(routef,"Nanital-");
    }
    if(s==5)
    {
        printf("Muzaffarnagar-");
        strcat(routef,"Muzaffarnagar-");
    }
    printSolution(path,s,d);

    if(d==0)
    {
       printf("-Delhi");
       strcat(routef,"-Delhi");
    }
    if(d==1)
    {
       printf("-Dehradun");
       strcat(routef,"-Dehradun");
    }
    if(d==2)
    {
       printf("-Ramnagar");
       strcat(routef,"-Ramnagar");
    }
    if(d==3)
    {
       printf("-Mussorie");
       strcat(routef,"-Mussorie");
    }
    if(d==4)
    {
       printf("-Nanital");
       strcat(routef,"-Nanital");
    }
    if(d==5)
    {
       printf("-Muzaffarnagar");
       strcat(routef,"-Muzaffarnagar");
    }
    if(flag!=1)
    {
      write_route(routef);
    }
return ans;
}
int main(int argc, char* argv[]) {
int deciding_var=0, temp_var=0, tsp_var=0,files=0;
char ch = 'y';
int flag = 0, x, temp;
char g[2];
int ctr=0;
while (ch == 'y' || ch=='Y')
{
system("cls");
char str[100], str2[100];

printf("\tMINOR 1 PROJECT: Application To implement and compare different shortest path algorithms \n");
printf("\n\nThe project takes into consideration a number of selected routes of Inter State Bus Terminals (ISBT) and presents \na proposal for the User to compute the Shortest Distance and Minimum Fare between the Source Destination \n of the User and the Final Destination of the User using different Shortest Path Algorithms and further their \ncomparison based on their Complexities and also to compute the minimum cities tour cost, distance and route \nfrom the entered Source Destination to all the other destinations");
printf("\n\n\tWelcome To Inter State Bus Terminal Application \n");
printf("\n\n\tDestinations Available: \n Delhi \n Dehradun \n Ramnagar \n Mussorie\n Nanital\n Muzaffarnagar\n");

printf("\n\n\tPlease Enter The Source Destination: \n\t\t");
if(ctr>=1)
gets(g);
gets(str);
if (strcmp(str, "Delhi") == 0)
flag = 1;
if (strcmp(str, "Dehradun") == 0)
flag = 1;
if (strcmp(str, "Ramnagar") == 0)
flag = 1;
if (strcmp(str, "Mussorie") == 0)
flag = 1;
if (strcmp(str, "Nanital") == 0)
flag = 1;
if (strcmp(str, "Muzaffarnagar") == 0)
flag = 1;
if (flag == 0)
{
printf("\n\tPlease enter a valid Source Destination");
exit(0);
}
flag = 0;
printf("\n\n\tPlease Enter The Final Destinaton: \n\t\t");
gets(str2);

if (strcmp(str, "Delhi") == 0)
flag = 1;
if (strcmp(str, "Dehradun") == 0)
flag = 1;
if (strcmp(str, "Ramnagar") == 0)
flag = 1;
if (strcmp(str, "Mussorie") == 0)
flag = 1;
if (strcmp(str, "Nanital") == 0)
flag = 1;
if (strcmp(str, "Muzaffarnagar") == 0)
flag = 1;

if (flag == 0)
{
printf("\n\tPlease enter a valid Final Destination");
exit(0);
}
if (strcmp(str2, "Delhi") == 0)
{
temp = 0;
}
if (strcmp(str2, "Dehradun") == 0)
{
temp = 1;
}
if (strcmp(str2, "Ramnagar") == 0)
{
temp = 2;
}
if (strcmp(str2, "Mussorie") == 0)
{
temp = 3;
}
if (strcmp(str2, "Nanital") == 0)
{
temp = 4;
}
if (strcmp(str2, "Muzaffarnagar") == 0)
{
temp = 5;
}
printf("\n\n\tBuses Available to travel: \n");
printf("\t\t1. Ordinary Bus\n");
printf("\t\t2. Express Bus\n");
printf("\t\t3. Semi Deluxe\n");
printf("\t\t4. Deluxe\n");
printf("\t\t5. Air-Conditioned\n");
printf("\tPlease select your choice\n\t");
scanf ("\n%d",&choice);
printf("\n\n\tWhich Algorithm you would like to prefer?");
printf("\n\t\t1. Algorithm Based on Johnson's Algorithm \n");
printf("\t\t2. Floyd Warshall Algorithm \n");
printf("\t\t3. Comparision of the above algorithms");
printf("\n\tPlease Enter A Value\n\t\t");
scanf("%d", &x);
if(x==3){
temp_var=1;
tsp_var=1;
files=1;
}
if(x!=3)
{
bool exist = read_file(str, str2);
if (exist == true)
    {
  deciding_var=1;
       char names[6][100] = { {"Delhi"},{"Dehradun"},{"Ramnagar"},{"Mussorie"},{"Nanital"},{"Muzaffarnagar"} };
       int i;
       for (i = 0; i < 4; i++)
       {
          if (strcmp(names[i], str) == 0)
          {
              start = i;
              break;
          }
       }
    }
}
int res;
if(deciding_var==0) {

if (x == 1 || x==3)
{
int Map[A][A] = {
                  {0,0,261,0,0,124} ,
                  {0,0,222,40,0,111} ,
                  {261,222,0,0,64,0} ,
                  {0,40,0,0,0,0},
                  {0,0,64,0,0,0},
                  {124,111,0,0,0,0}
};

if (strcmp(str, "Delhi") == 0)
{
if(temp_var==1)
{
printf("\n\t\tAnalysis Of Johnson's Algorithm");
start = 0;
        double total_time;
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
        res = dijkstra(Map, A, 0, temp,choice,files);
        clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
        printf("\n\t\tTime taken to print for the Johnson's Algorithm is: %f seconds\n\n", total_time);
}
else{
start = 0;
res = dijkstra(Map, A, 0, temp,choice,files);
}
}
if (strcmp(str, "Dehradun") == 0)
{
if(temp_var==1)
{
printf("\n\t\tAnalysis Of Johnson's Algorithm");
start = 1;
        double total_time;
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
        res = dijkstra(Map, A, 1, temp,choice,files);
        clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
        printf("\n\n\t\tTime taken to print for the Johnson's Algorithm is: %f seconds\n\n", total_time);
}
else{
start = 1;
res = dijkstra(Map, A, 1, temp,choice,files);
}
}
if (strcmp(str, "Ramnagar") == 0)
{
if(temp_var==1)
{
printf("\n\t\tAnalysis Of Johnson's Algorithm");
start = 2;
        double total_time;
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
        res = dijkstra(Map, A, 2, temp,choice,files);
        clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
        printf("\n\t\tTime taken to print for the Johnson's Algorithm is: %f seconds\n\n", total_time);
}
else{
start = 2;
res = dijkstra(Map, A, 2, temp,choice,files);
}
}
if (strcmp(str, "Mussorie") == 0)
{
if(temp_var==1)
{
printf("\n\t\tAnalysis Of Johnson's Algorithm");
start = 3;
        double total_time;
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
        res = dijkstra(Map, A, 3, temp,choice,files);
        clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
        printf("\n\t\tTime taken to print for the Johnson's Algorithm is: %f seconds\n\n", total_time);
}
else{
start = 3;
res = dijkstra(Map, A, 3, temp,choice,files);
}
}
if (strcmp(str, "Nanital") == 0)
{
if(temp_var==1)
{
printf("\n\t\tAnalysis Of Johnson's Algorithm");
start = 4;
        double total_time;
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
        res = dijkstra(Map, A, 4, temp,choice,files);
        clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
        printf("\n\t\tTime taken to print for the Johnson's Algorithm is: %f seconds\n\n", total_time);
}
else{
start = 4;
res = dijkstra(Map, A, 4, temp,choice,files);
}
}
if (strcmp(str, "Muzaffarnagar") == 0)
{
if(temp_var==1)
{
printf("\n\t\tAnalysis Of Johnson's Algorithm");
start = 5;
        double total_time;
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
        res = dijkstra(Map, A, 5, temp,choice,files);
        clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
        printf("\n\t\tTime taken to print for the Johnson's Algorithm is: %f seconds\n\n", total_time);
}
else{
start = 5;
res = dijkstra(Map, A, 5, temp,choice,files);
}
}
}
if (x == 2 || x==3)
{
printf("\t\t");
char names[6][100] = { {"Delhi"},{"Dehradun"},{"Ramnagar"},{"Mussorie"},{"Nanital"},{"Muzaffarnagar"} };
int array[A][A]={
                  {0,9999,261,9999,9999,124} ,
                  {9999,0,222,40,9999,111} ,
                  {261,222,0,9999,64,9999} ,
                  {9999,40,9999,0,9999,9999},
                  {9999,9999,64,9999,0,9999},
                  {124,111,9999,9999,9999,0}
                };  
if (strcmp(str, "Delhi") == 0)
{
start = 0;
char *temp1="";
strcpy(routef,temp1);
strcat(routef, "");
strcat(routef, names[start]);
strcat(routef, ":");
strcat(routef, names[temp]);
strcat(routef, " ");
if(temp_var==1)
{
printf("\n\t\tAnalysis Of Floyd's Algorithm\n\t\t");
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
res = helper_FLOYD(0, temp, array, A,files);
clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
}
else{
res = helper_FLOYD(0, temp, array, A,files);
}
}
if (strcmp(str, "Dehradun") == 0)
{
start = 1;
char *temp1="";
strcpy(routef,temp1);
strcat(routef, "");
strcat(routef, names[start]);
strcat(routef, ":");
strcat(routef, names[temp]);
strcat(routef, " ");
if(temp_var==1)
{
printf("\n\t\tAnalysis Of Floyd's Algorithm\n\t\t");
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
res = helper_FLOYD(1, temp, array, A,files);
clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
}
else{
res = helper_FLOYD(1, temp, array, A,files);
}
}
if (strcmp(str, "Ramnagar") == 0)
{
start = 2;
char *temp1="";
strcpy(routef,temp1);
strcat(routef, "");
strcat(routef, names[start]);
strcat(routef, ":");
strcat(routef, names[temp]);
strcat(routef, " ");
if(temp_var==1)
{
   printf("\n\t\tAnalysis Of Floyd's Algorithm\n\t\t");
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
   res = helper_FLOYD(2, temp, array, A,files);
   clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
}
else{
   res = helper_FLOYD(2, temp, array, A,files);
}
}
if (strcmp(str, "Mussorie") == 0)
{
start = 3;
char *temp1="";
strcpy(routef,temp1);
strcat(routef, "");
strcat(routef, names[start]);
strcat(routef, ":");
strcat(routef, names[temp]);
strcat(routef, " ");
if(temp_var==1)
{
   printf("\n\t\tAnalysis Of Floyd's Algorithm\n\t\t");
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
   res = helper_FLOYD(3, temp, array, A,files);
   clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
}
else{
   res = helper_FLOYD(3, temp, array, A,files);
}
}


if (strcmp(str, "Nanital") == 0)
{
start = 4;
char *temp1="";
strcpy(routef,temp1);
strcat(routef, "");
strcat(routef, names[start]);
strcat(routef, ":");
strcat(routef, names[temp]);
strcat(routef, " ");
if(temp_var==1)
{
printf("\n\t\tAnalysis Of Floyd's Algorithm\n\t\t");
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
res = helper_FLOYD(4, temp, array, A,files);
clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
}
else{
res = helper_FLOYD(4, temp, array, A,files);
}
}
if (strcmp(str, "Muzaffarnagar") == 0)
{
start = 5;
char *temp1="";
strcpy(routef,temp1);
strcat(routef, "");
strcat(routef, names[start]);
strcat(routef, ":");
strcat(routef, names[temp]);
strcat(routef, " ");
if(temp_var==1)
{
printf("\n\t\tAnalysis Of Floyd's Algorithm\n\t\t");
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
res = helper_FLOYD(5, temp, array, A,files);
clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
}
else{
res = helper_FLOYD(5, temp, array, A,files);
}
}

printf("\n\t\tThe shortest distance between %s and %s is %d units\n\t\t", str, str2, res);
Calculate_Cost(res,choice);
if(temp_var==1)
{
printf("\n\n\t\tTime taken to print for the Floyd's Algorithm is: %f seconds\n", total_time);
}
}
if(temp_var!=1)
{
write_file(str, str2, res);
}
}

char names[6][100] = { {"Delhi"},{"Dehradun"},{"Ramnagar"},{"Mussorie"},{"Nanital"},{"Muzaffarnagar"} };
int i;
for (i = 0; i < 6; i++)
{
if (strcmp(names[i], str) == 0)
{
start = i;
break;
}
}
bool readtsp;
if(tsp_var==1)
{
printf("\n\n\t\tAnalysis of Travelling Salesman Algorithm");
}
printf("\n\t\tThe tour from the source can be carried out using following route: \n\t\t");
if(tsp_var!=1)
{
readtsp = read_tsp(names[start]);
}
if(tsp_var==1){
readtsp=false;
}
if (readtsp == false)
{
int completed[10]={0,0,0,0,0,0,0,0,0,0};
cost=0;
char ttsp[10]="";
strcpy(tspRoute,ttsp);
strcat(tspRoute,names[start]);
if(tsp_var==1)
{
        clock_t start_time=clock();
        //time count starts
        srand(time(NULL));
   mincost(start,completed);
   clock_t end_time = clock();
        //time count stops
        total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        //calulate total time
       
}
else{
mincost(start,completed);
}
strcat(tspRoute," ");
char cc[5];
sprintf(cc,"%d",cost);
strcat(tspRoute,cc);
if(temp_var!=1)
{
write_tsp();
}
printf("\n\t\tThe minimum distance for the route is : %d\n\t\t", cost);
Calculate_Cost(cost,choice);
if(temp_var==1)
{
printf("\n\n\t\tTime taken to print for the TSP Algorithm is: %f seconds\n", total_time);
}
}
ctr++;
deciding_var=0;
temp_var=0;
tsp_var=0;
files=0;
printf("\n\tDo you want to continue?(Y/N)\n\t\t");
scanf("%s", &ch);
}
return 0;
}
