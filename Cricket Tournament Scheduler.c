//import all header files

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//all function prototypes//

int tournamentMenu(); //used only at the beginning of the program
char** Teams(int teamcount); // used only at beginning 
char** venues(int venuecount); //used only at beginning
int** Initial_Tournament_Data(int teamcount); //used only once
int**Initial_teams_Data(int teams);  //used only once
int teamA_selection(int teamcount,int**data_of_teams,int*previous_day_Array,int**match_matrix);//used frequently
int teamB_selection(int teamA,int**match_Matrix,int**teams_Data,int*previous_day_array);//used frequently
void previous_day(int teamA,int teamB,int*previous_day_array);//used frequently
void Match_Matrix_editor(int teamA,int teamB,int teamcount,int**match_matrix);//used frequently
void teams_data_editor(int team1,int team2,int**teams_Data,int element);//used frequently
int*match_matrix_finisher(int**match_matrix,int teamcount); //used only at the end and only once
int** match_history(int**match_history_matrix,int total_matches,int*left_over_matches,int count_of_rem_matches); //used only once at end
int*Date(int*p);//used while printing the schedule
void print_schedule(int**match_history_matrix,char**venuelist,int venuesize,char**teamlist);//used at last
void Round_robin_format(char**teamlist,char**venuelist,int teamcount,int venuecount);//functions that zips all the above function


//the main function begins here//

int main(){

    srand(time(NULL)); //set random seed based on the time of execution so that we get different random number sequences everytime

    //the  user will choose the tournament type that he/she wants to play
    int tournament_choice = tournamentMenu();

    int teamcount,venuecount;

    if(tournament_choice==1){
        char*teamlist[10];
        char*venuelist[10];
        // if user chose world cup , then by default 10 teams and 10 venues will be assigned
        teamcount=10;
        venuecount=10;
        char teams[10][51]={"India","Australia","New Zealand","England","South Africa","Pakistan","Sri Lanka","Afghanistan","West Indies","Bangladesh"};
        char venues[10][51]={"chennai","mumbai","kolkata","ahmedabad","lucknow","dharamshala","delhi","bangalore","hyderabad","shimla"};
        for (int i = 0; i < teamcount; ++i) {
        teamlist[i] = teams[i];
        }

        for (int i = 0; i < venuecount; ++i) {
        venuelist[i] = venues[i];
        }
        Round_robin_format(teamlist,venuelist,teamcount,venuecount);

    }
    else if(tournament_choice==2){
        char*teamlist[10];
        char*venuelist[10];
        // if the user chose IPL , then by default 10 teams and 10 venues will be assigned
        teamcount=10;
        venuecount=10;
        char teams[10][51]={"CSK","RCB","MI","LSG","GT","KKR","SRH","PBKS","RR","DC"};
        char venues[10][51]={"chennai","mumbai","kolkata","ahmedabad","lucknow","dharamshala","delhi","bangalore","hyderabad","Jaipur"};
        for (int i = 0; i < teamcount; ++i) {
        teamlist[i] = teams[i];
        }

        for (int i = 0; i < venuecount; ++i) {
        venuelist[i] = venues[i];
        }
        Round_robin_format(teamlist,venuelist,teamcount,venuecount);
    }
    else{
        char**teamlist;
        char**venuelist;
        // if the user chose customized tournament , then user can define the number of teams , number of venues, list of team names and list of 
        // venues names 
        printf("enter the number of teams that you want:");
        scanf("%d",&teamcount);
        printf("enter the number of venues that you want:");
        scanf("%d",&venuecount);
        teamlist = Teams(teamcount);//Teams is a function that receives number of teams and 
        //creates an array of user-inputted team names and returns the array
        venuelist = venues(venuecount);//venues is a function that receives number of venues and 
        //creates an array of user-inputted venue names and returns the array
        //the function round_robin_format is executed
        Round_robin_format(teamlist,venuelist,teamcount,venuecount);
    }

    return 0;
}

//function definitions//


int tournamentMenu(){
    /*task: it prints out what are the tournaments available
            and asks user to select one from the given choice 
            returns that choice*/
    printf("\n\nHello Welcome to the Cricket Tournament Scheduler!\n\n"
           "select the Tournament that you want to schedule\n"
           "choice            Tournaments\n"
           "  1               The World Cup\n"
           "  2               The Indian Premiere League\n"
           "  3               Customized Tournaments\n");
    printf("\nplease enter the choice that you want to choose:");
    int choice_Of_Tournament;
    scanf("%d",&choice_Of_Tournament);
    switch(choice_Of_Tournament){
        case 1:
            printf("\nThe World Cup is loading for you...\n");
            break;
        case 2:
            printf("\nThe Indian Premiere League is loading for you...\n");
            break;
        case 3:
            printf("\nWow Sure your custom tournament is getting ready...\n");
            break;
        default:
            printf("\n Sorry the choice that you have provided is invalid");
            return tournamentMenu();  
    }
    return choice_Of_Tournament;
}


int randNatural(int n){
    //task: it selects a random from 1 to n and returns that random n
    double random_number = rand()*n + 1;
    return (int)random_number;
}


char** Teams(int teamcount){
    // it receives the number of teams from the user and creates an array of team names and returns that array 
    char**teamlist;
    teamlist=(char**)calloc(teamcount,sizeof(char*));// dynamic memory allocation function 
    for(int i=0;i<teamcount;i++){
        teamlist[i]=(char*)calloc(51,sizeof(char));
        printf("enter the team %d name:",i+1);
        scanf("%s",teamlist[i]);
    }
    return teamlist;
}


char** venues(int venuecount){
    // it receives the number of venues from the user and creates an array of venue names and returns that array 
    char**venuelist;
    venuelist=(char**)calloc(venuecount,sizeof(char*));
    for(int i=0;i<venuecount;i++){
        venuelist[i]=(char*)calloc(51,sizeof(char));
        printf("enter the venue %d name:",i+1);
        scanf("%s",venuelist[i]);
    }
    return venuelist;
}


int** Initial_Tournament_Data(int teamcount){
    //it receives the no.of teams 
    // creates initial tournament data which will be the initial match matrix before starting tournament
    // what is the initial tournament data ? it is a matrix of order ( n x n ) for n number of teams 
    // each row is assigned to a particular team 
    //first column contains the information of number of matches the team is yet to play
    // all other columns of one particular row contain the information of which teams are yet to play with this team
    int**teamrows=(int**)calloc(teamcount,sizeof(int*));
    for(int i=0;i<teamcount;i++){
        teamrows[i]=(int*)calloc(teamcount,sizeof(int));
        teamrows[i][0]=teamcount-1; //totally they need to play (teamcount - 1) matches
    }
    int k;
    for(int i=0;i<teamcount;i++){
        k=1;
        for(int j=1;j<=teamcount;j++){
            if(j==i+1){
                continue;
            }
            teamrows[i][k]=j;
            k++;
        }
    }
    return teamrows;
}


int**Initial_teams_Data(int teams){
    //no.of teams is passed on to the function and a matrix called initial_data is created which contains brief data of teams 
    //it returns the initial data , which is the initial teams_data matrix before tournament begins
    //the first row first column element contains the information of number of teams having non-zero number of matches left
    //after that the first row contains the number of matches left for each team
    //in the second row the team corresponding to the number of matches left is written
    // it is a shorter version of the match_matrix ,where there are two rows. second row contains the team numbers
    //first row contains the corresponding no.of matches left
    int**initial_data=(int**)calloc(2,sizeof(int*));
    for(int i=0;i<2;i++){
        initial_data[i]=(int*)calloc(teams+1,sizeof(int));
    }
    //a matrix of 2 rows and n+1 columns is made , where n is the number of teams
    initial_data[0][0]=teams;
    initial_data[1][0]=0;
    for(int i=1;i<=teams;i++){//filling with number of matches left for each team. Initially they have n-1 matches left, if n teams are present
        initial_data[0][i]=teams-1;
    }
    for(int i=1;i<=teams;i++){//filling the corresponding team numbers 
        initial_data[1][i]=i;
    }
    return initial_data; 
}


int factorial(int n){
    //returns the factorial of a given number n
    //this is useful while using combinatorial mathematics application
    if(n==0){
        return 1;
    }
    return n*factorial(n-1);
}


int teamA_selection(int teamcount,int**data_of_teams,int*previous_day_Array,int**match_matrix){
    /* this function is responsible for selecting randomly the first team out of two teams to be played on a given day
       it cannot randomly select a team simply. it has to select the team based on a given set of conditions 

       1) the team should not have played just the previous match
       2) the team should have non-zero number of matches left
       3) the team which has only matches with the previous-match teams must not be selected
    
    */
    int teams_data_size= data_of_teams[0][0]; //teams_data_size holds the number of teams that have non-zero number of matches left
    int array[teams_data_size];
    int size=0;
    int a = previous_day_Array[0];
    int b = previous_day_Array[1];
    //a and b hold the team1 and team2 that played the previous match
    //we should not select that team1 which has only team2 yet to play and team2 played yesterday
    for(int i=1;i<=teams_data_size;i++){

        int team=data_of_teams[1][i];
        if(match_matrix[team-1][0]==1 && (match_matrix[team-1][1]==a ||match_matrix[team-1][1]==b ) ){
            // if the team has only 1 match left and that is against a or b
            continue;
        }
        if(match_matrix[team-1][0]==2 && ((match_matrix[team-1][1]==a && match_matrix[team-1][2]==b) || (match_matrix[team-1][1]==b && match_matrix[team-1][2]==a))){
            // if the team has only 2 matches left and that is against a and b
            continue;
        }
        if(team==a || team==b){
            //if the selected team is either a or b
            continue;
        }
        //when none of the 3 if-conditions above satifies , then we add that team to the array
        array[size]=team;
        size++;
    }
    //now the array consists of the teams that satisfies the conditions
    //size is the number of teams that meets the following conditions (it is the number of teams that are present in "array" array)
    if(size==0){
        //we return 0 , if we find a case when any team selected has matches only with the previous-day participants
        //this conditional statement is such that it will be satisfied only during the last stage of the tournament
        return 0;
    }
    int random_number = rand()%size; //generating a random number between and including 0 and size-1
    return array[random_number]; //it returns the team corresponding to the random index - that will be the team1

}

int teamB_selection(int teamA,int**match_Matrix,int**teams_Data,int*previous_day_array){
    /*
    this function is responsible for the second team out of the two teams to be played in a given match
    teamB is selected following the given conditions:
    1) teamB must not be same as teamA
    2) teamB must not have played the previous match
    3) teamB must have non-zero number of matches left
    4) teamB must not have played against teamA before
    
    */
    int a = previous_day_array[0];
    int b = previous_day_array[1];
    int size1=match_Matrix[teamA-1][0]; //size1 is the number of matches left for teamA
    int array1[size1];
    int index1=0;
    for(int i=1;i<=size1;i++){
        //storing all elements which are part of teamA row except previous day teams
        if(match_Matrix[teamA-1][i]!=a && match_Matrix[teamA-1][i]!=b){
            array1[index1]=match_Matrix[teamA-1][i];
            index1++;
        }
    }
    size1=index1;//index1 contains the size of the array1
    int array2[size1]; //another array2 is created of the same size as proper array1
    int index2=0;
    for(int i=0;i<size1;i++){
        int ele1=array1[i];
        for(int j=1;j<=teams_Data[0][0];j++){
            int ele2=teams_Data[1][j];
            if(ele1==ele2){//this is for checking if the teams stored in array1 have non-zero matches left. those teams are added to array2
                array2[index2]=ele1;
                index2++;
            }
        }
    }
    int size2=index2;//index2 holds the  proper size of array2
    int random_int = rand()%size2; //random_int is the integer between and including 0 and size2 - 1
    return array2[random_int]; //teamB is returned

}


void previous_day(int teamA,int teamB,int*previous_day_array){
    /* the task of this function is to get teamA, teamB and the previous_day_array and 
        to edit the previous_day_Array with the new teamA and teamB
    */
    previous_day_array[0]=teamA;
    previous_day_array[1]=teamB;
}


void Match_Matrix_editor(int teamA,int teamB,int teamcount,int**match_matrix){
    /*
    this function plays a huge role in the program by modifying the data present in the match matrix after each match is declared
    this takes the parameters teamA , teamB , teamcount (number_of_teams) and the match_matrix
    task : after a match is declared , the teamA will be removed from teamB's row and the teamB will be removed from the teamA's row
    the no.of matches left for each team is subtracted by 1
    */
    int sizeA=match_matrix[teamA-1][0]; //number of matches left for teamA
    int sizeB=match_matrix[teamB-1][0]; //number of matches left for teamB
    for(int i=1;i<sizeA;i++){
        if(match_matrix[teamA-1][i]!=teamB){//if the number in teamA row is not equal to teamB
            continue;
        }
        match_matrix[teamA-1][i]=match_matrix[teamA-1][i+1];
        match_matrix[teamA-1][i+1]=teamB;
        //if we found teamB on the row of teamA , we iteratively swap and put the teamB to the end of the row
    }
    for(int i=1;i<sizeB;i++){
        if(match_matrix[teamB-1][i]!=teamA){//if the number in teamB row is not equal to teamA
            continue;
        }
        match_matrix[teamB-1][i]=match_matrix[teamB-1][i+1];
        match_matrix[teamB-1][i+1]=teamA;
        //if we found teamA on the row of teamB , we iteratively swap and put the teamA to the end of the row
    }
    match_matrix[teamA-1][sizeA]=0;// the place holding by teamB after swapping is overwritten by 0
    match_matrix[teamB-1][sizeB]=0;// the place holding by teamA after swapping is overwritten by 0
    match_matrix[teamA-1][0]=match_matrix[teamA-1][0]-1; //subtracting 1 from the no.of matches left for teamA
    match_matrix[teamB-1][0]=match_matrix[teamB-1][0]-1; //subtracting 1 from the no.of matches left for teamB
   
}


void teams_data_editor(int team1,int team2,int**teams_Data,int element){
    /* 
    the task of this function is to edit the teams_data_matrix
    we need to subtract the no. of the matches by 1 for both the teams
    we need to check if any team now has 0 matches...and accordingly that team is shifted to the end of the row
    this function is also very important and is used everytime a match is declared
    */
    int size = teams_Data[0][0]; //size holds the number of teams having non-zero number of matches 
    int team1_ind;
    int team2_ind;
    //check the index of team1
    for(int i=1;i<=size;i++){//finding the index of team 1
        if(teams_Data[1][i]==team1){
            team1_ind=i;
            break;
        }
    }
    int first_time=1;
    //check the index of team2
    for(int i=1;i<=size;i++){//finding the index of team 2
        if(teams_Data[1][i]==team2){
            team2_ind=i;
            break;
        }
    }
    teams_Data[0][team1_ind]=teams_Data[0][team1_ind]-1;//reducing the no.of matches of team1 by 1
    teams_Data[0][team2_ind]=teams_Data[0][team2_ind]-1;//reducing the no.of matches of team2 by 1
    int loopsize;
    if(teams_Data[0][team1_ind]==0 && teams_Data[0][team2_ind]==0){
        //both become zero at the same time
        loopsize=2;
        teams_Data[0][0]-=2;
    }
    else if(teams_Data[0][team1_ind]!=0 && teams_Data[0][team2_ind]!=0){
        //both did not become zero at the same time
        loopsize=0;
    }
    else{
        //any one of them became zero at the same time
        loopsize=1;
        teams_Data[0][0]-=1;
    }
    //editing the teams data
    for(int j=0;j<loopsize;j++){//no.of times to repeat the whole swapping process
        for(int i=1;i<=size-1;i++){
            //iterative swapping if any one of the team has zero matches now
            if(teams_Data[0][i]!=0){
                continue;
            }
            int temp1=teams_Data[0][i];
            int temp2=teams_Data[1][i];
            teams_Data[0][i]=teams_Data[0][i+1];
            teams_Data[1][i]=teams_Data[1][i+1];
            teams_Data[0][i+1]=temp1;
            teams_Data[1][i+1]=temp2;
        }
    }
    return;
}


int*match_matrix_finisher(int**match_matrix,int teamcount){
    /*this function is used once when the teamA_Selection function returns 0 to the team1
      task: it inputs the match_matrix and gathers the data of all remaining matches and puts it in an array and returns that array
    */
    int size=0;
    for(int i=0;i<teamcount;i++){
        size=size+match_matrix[i][0];
    } //size is the sum of the first column of match_matrix which is also equal to the size of the array to be returned
    int*array=(int*)calloc(size,sizeof(int));
    int index=0;
    for(int i=0;i<teamcount && index<size;i++){
        if(match_matrix[i][0]!=0){ //if the team of the row having non-zero number of matches
            int teamA=i+1; 
            int teamB=match_matrix[i][1];
            //storing both the teams in the array
            array[index]=teamA;
            array[index+1]=teamB;
            index=index+2;
            Match_Matrix_editor(teamA,teamB,teamcount,match_matrix);//use the match matrix editor to edit
            i=i-1;//we do this assignment because we need to check the same row again...
            //     it is possible that a given team may have more than one match left
        }
    }
    return array;
}


int** match_history(int**match_history_matrix,int total_matches,int*left_over_matches,int count_of_rem_matches){
    /*
    match_history is a function that deals with the match_history_matrix
    match_history_matrix stores the data of matches of the tournament which will be printed finally
    after the match_matrix_finisher function is executed , this match_history function is executed
    task : left_over_matches array is provided by the matrix_match_finisher function , which contains the data of remaining matches
    this function now uses that data from the array and alters the match_history matrix
    it will find the correct spot for the match of given two teams in the match history matrix and alters the match_history
    */
    int matches_decided = total_matches-count_of_rem_matches;//total number of matches assigned so far
    int a,b,j=1;
    int array_match[count_of_rem_matches];
    int array1_index=0;//index counter for the array_match array
    int left_index=0; //index counter for the left_over_matches array

    //we will create a new match_history_matrix that will be returned by this function
    int**new_match_history_matrix = (int**)calloc(total_matches+1,sizeof(int*));
    for(int i=0;i<total_matches+1;i++){
        new_match_history_matrix[i]=(int*)calloc(2,sizeof(int));
    }
    loop: //this is for goto statement
    for(int i=1;i<matches_decided && array1_index<count_of_rem_matches;i++){
        //this for-loop is used to find the index of the match_history matrix that can be filled by the unassigned match
        a = left_over_matches[left_index];b=left_over_matches[left_index+1];
        if(a!=match_history_matrix[i][0] && a!=match_history_matrix[i][1] && a!=match_history_matrix[i+1][0] && a!=match_history_matrix[i+1][1]&&
           b!=match_history_matrix[i][0] && b!=match_history_matrix[i][1] && b!=match_history_matrix[i+1][0] && b!=match_history_matrix[i+1][1]){
                array_match[array1_index]=i+1;
                array1_index++;
                left_index=left_index+2;
           }
    }
    if(array1_index<count_of_rem_matches){
        //if the for loop finishes without finding a new spot then we assign the position after all rows
        array_match[array1_index]=matches_decided + j;
        array1_index++;
        j++;
        left_index=left_index+2;
        goto loop; //we again go to the loop once if matches are still pending in the left_over_matches array      
    }
    //editing the new match history matrix
    new_match_history_matrix[0][0]=total_matches; 
    int added=0,q=1; //added is a flag variable and q is iterating variable for the old match_history matrix
    left_index=0;
    for(int i=1;i<=total_matches;i++){
        added=0;
        for(int k=0;k<count_of_rem_matches;k++){
            if(array_match[k]==i){ //if the assigned row for a match comes during iteration , we add that match in this position
                new_match_history_matrix[i][0]=left_over_matches[left_index];
                new_match_history_matrix[i][1]=left_over_matches[left_index+1];
                left_index=left_index+2;
                added=1;//we give the status 1 to the added variable which acts as a flag
                break;
            }
        }
        if(added==1){
            continue;
        }
        else{// if the assigned row for a match does not come during iteration, the added variable remains zero and we simply copy from 
            //old match_history matrix to the new match_history matrix
            new_match_history_matrix[i][0]=match_history_matrix[q][0];
            new_match_history_matrix[i][1]=match_history_matrix[q][1];
            q++;
        }
    }
    return new_match_history_matrix;
}

int*Date(int*p){
    //it is a function that deals with the date. it takes the array containing date and month and changes it to the next date and returns that array
    int month=p[1];
    int date=p[0];
    int max;
    switch(month){
        case 1:
            max=31;
            break;
        case 2:
            max=28;
            break;
        case 3:
            max=31;
            break;
        case 4:
            max=30;
            break;
        case 5:
            max=31;
            break;
        case 6:
            max=30;
            break;
        case 7:
            max=31;
            break;
        case 8:
            max=31;
            break;
        case 9:
            max=30;
            break;
        case 10:
            max=31;
            break;
        case 11:
            max=30;
            break;
        case 12:
            max=31;
            break;
    }
    if(date<max){
        p[0]++;
    }
    if(date==max){
        p[0]=1;
        p[1]++;
    }
    if(date==max && month==12){
        p[0]=1;
        p[1]=1;
    }
    return p;
}


void print_schedule(int**match_history_matrix,char**venuelist,int venuesize,char**teamlist){
    /*it is the function that deals with printing the schedule given the match_history matrix , teamlist and the venuelist*/
    printf("when do you want the tourament to begin!:\n");
    printf("enter the date: ");
    int date,month;
    scanf("%d",&date);
    printf("enter the month: ");
    scanf("%d",&month);
    int*p=(int*)calloc(2,sizeof(int));
    p[0]=date;
    p[1]=month;
    printf("here goes the schedule : \n\n\n");
    printf("match_number    match                                                   date        time        venue\n");
    for(int i=1;i<=match_history_matrix[0][0];i++){
        int team1=match_history_matrix[i][0];
        int team2=match_history_matrix[i][1];
        int random_venue = rand()%venuesize;
        printf("%d     %s vs %s      %14d/%d         19:00 hrs           %s\n",i,teamlist[team1-1],teamlist[team2-1],p[0],p[1],venuelist[random_venue]);
        Date(p);
    }
}


void Round_robin_format(char**teamlist,char**venuelist,int teamcount,int venuecount){
    /*this function is just a function that contains all other functions in action to produce the complete output
    */
    int**match_matrix = Initial_Tournament_Data(teamcount);
    int**teams_Data = Initial_teams_Data(teamcount);
    int previous_day_array[2]={0,0};
    int team1,team2;
    int total_matches = factorial(teamcount)/(factorial(2)*factorial(teamcount-2));
    int**match_history_matrix=(int**)calloc(total_matches+1,sizeof(int*));
    for(int i=0;i<=total_matches;i++){
        match_history_matrix[i]=(int*)calloc(2,sizeof(int));
    }
    match_history_matrix[0][0]=total_matches;
    int i=1;
    while(teams_Data[0][0]!=0){
        team1=teamA_selection(teamcount,teams_Data,previous_day_array,match_matrix);
        if(team1==0){
            printf("going to edit match_history_matrix:\n");
            int*remaining_matches_array=match_matrix_finisher(match_matrix,teamcount);
            match_history_matrix=match_history(match_history_matrix,total_matches,remaining_matches_array,total_matches-i+1);
            teams_Data[0][0]=0;
            break;
        }
        team2=teamB_selection(team1,match_matrix,teams_Data,previous_day_array);
        match_history_matrix[i][0]=team1;
        match_history_matrix[i][1]=team2;
        i++;
        previous_day(team1,team2,previous_day_array);
        Match_Matrix_editor(team1,team2,teamcount,match_matrix);
        teams_data_editor(team1,team2,teams_Data,1);  
    }
    print_schedule(match_history_matrix,venuelist,teamcount,teamlist);
}
