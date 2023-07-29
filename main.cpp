#include <iostream>
#include <list>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

class task{
    public: 
    string todo;
    int val;
    task(string todo, int val){
        this->todo=todo;
        this->val=val;
    }
    friend ostream& operator<<(ostream& os, const task t);
};
class reward{
    public:
    string name;
    int points;
    reward(string name, int points){
        this->name=name;
        this->points=points;
    }
    friend ostream& operator<<(ostream& os, const reward r);
};
ostream& operator<<(ostream& os, task t){
    os << t.todo <<endl<< t.val<<endl;
    return os;
}
ostream& operator<<(ostream& os, reward r){
    os << r.name << endl<< r.points <<endl;
    return os;
}
class todoData{
    public:
    int totalPoints;

    list<task> taskList;

    list<reward> rewardList;

    todoData(int points){
        this->totalPoints=points;
	}  
    void addTask(string todo, int val){
        this->taskList.emplace_back(task(todo,val));
    }
    void completeTask(int num){
        list<task> newTasks;
        for(int i=0;i<num-1;i++){
            newTasks.emplace_back(taskList.front());
            taskList.pop_front();
        }
        task complete = taskList.front();
        totalPoints+=complete.val;
        taskList.pop_front();
        while(!taskList.empty()){
            newTasks.emplace_back(taskList.front());
            taskList.pop_front();
        }
        taskList=newTasks;
    }
    void deleteTask(int num){
        list<task> newTasks;
        for(int i=0;i<num-1;i++){
            newTasks.emplace_back(taskList.front());
            taskList.pop_front();
        }
        taskList.pop_front();
        while(!taskList.empty()){
            newTasks.emplace_back(taskList.front());
            taskList.pop_front();
        }
        taskList=newTasks;
    }
    void deleteReward(int num){
        //cout<<"enter delete task"<<endl;
        list<reward> newR;
        for(int i=0;i<num-1;i++){
            newR.emplace_back(rewardList.front());
            rewardList.pop_front();
        }
        rewardList.pop_front();
        while(!rewardList.empty()){
            newR.emplace_back(rewardList.front());
            rewardList.pop_front();
        }
        rewardList=newR;
    }
    void addReward(string rewardName, int price){
        this->rewardList.emplace_back(reward(rewardName,price));
    }
    void heading(){
        //heading
        system("clear");
        cout<<"___________________________________________________________________"<<endl;
        cout<<"-------------------------------------------------------------------"<<endl;
        cout<<"---------------------------- POINTS: "<<this->totalPoints<<" ----------------------------"<<endl<<endl;
    }
    int printToDo(){
        heading();
        int opt=0;
        cout<<"TASKS: "<<endl<<endl;
        if(taskList.empty()){
            cout<<"You have no tasks! Congratulations!"<<endl<<endl;
        }
        else{
            list<task> copyTasks = this->taskList;
           for(int i=0;i<this->taskList.size();i++){
                cout<<i+1<<". "<<copyTasks.front().todo<<" -- "<<copyTasks.front().val<<" points"<<endl;
                copyTasks.pop_front();
            } 
        }
        cout<<endl<<"Menu: "<<endl<<"1. Add Task"<<endl<<"2. Mark Task Complete"<<endl<<"3. Delete Task"<<endl<<"4. Return to Menu"<<endl<<endl;
        cout<<"Enter Option:  ";
        cin>>opt;
        return opt;
        
    }
    int printRewards(){
        heading();
        int opt=0;
        cout<<"SHOP: "<<endl<<endl;
        if(rewardList.empty()){
            cout<<"You have no current rewards."<<endl<<endl;
        }
        else{
            list<reward> copyRewards = this->rewardList;
           for(int i=0;i<this->rewardList.size();i++){
                cout<<i+1<<". "<<copyRewards.front().name<<endl<<"-- $"<<copyRewards.front().points<<endl;
                copyRewards.pop_front();
            } 
        }
        cout<<endl<<"Menu: "<<endl<<"1. Add Reward"<<endl<<"2. Purchase Reward"<<endl<<"3. Delete Reward"<<endl<<"4. Return to Menu"<<endl<<endl;
        cout<<"Enter Option:  ";
        cin>>opt;
        return opt;
    }
    int purchase(int num){
        for(int i=0;i<num-1;i++){
        }
        if(rewardList.front().points>totalPoints){
            return -1;
        }
        else{
            totalPoints-=rewardList.front().points;
            return 0;
        }
    }
    int printMenu(){
        //system("clear");
        heading();
        cout<<"MENU: "<<endl<<endl;
        cout<<"1. To Do List"<<endl;
        cout<<"2. Reward Shop"<<endl;
        cout<<"3. Save and Exit"<<endl<<endl;

        cout<<"Enter menu item number: ";

        int i=0;
        cin>>i;

        return i;

    }
};

int main(int argc, char * argv[]){
    //system("clear");
    //cout<<"start"<<endl;
    fstream log("pt.txt");
    int points=0;
    log>>points;
    log.close();
    todoData* t = new todoData(points);
    //arg 1 is task list
    fstream inTask;
    inTask.open(argv[1]);
    string taskName;
    string pointVal;
    for(string buff;getline(inTask,buff,'\n');){
        getline(inTask,pointVal,'\n');
        taskName=buff;
        t->addTask(taskName, stoi(pointVal));
    }
    inTask.close();
    //arg 2 is rewards list
    fstream inReward;
    inReward.open(argv[2]);
    string rewardName;
    string price;
    for (string buffer;getline (inReward,buffer,'\n'); ){
        getline(inReward,price,'\n');
        rewardName=buffer;
        t->addReward(rewardName, stoi(price));
    }
    
    inReward.close();

    int MenuOpt = 0;
    int opt=0;
    //cout<<"check"<<endl;
    while(MenuOpt!=3){
        MenuOpt = t->printMenu();
        while(MenuOpt == 1){
            opt=t->printToDo();
            if (opt==1){
                //add task
                string inputTodo;
                int inputVal=0;
                cout<<"Enter new task: ";
                cin.ignore();
                getline(cin,inputTodo);
                cout<<"Enter point value: ";
                cin>>inputVal;
                t->addTask(inputTodo,inputVal);
                continue;
            }
            else if (opt==2){
                //delete task, add to points
                int num=0;
                cout<<"Enter task number completed: ";
                cin>>num;
                t->completeTask(num);
                continue;

            }
            else if (opt==3){
                //delete task
                int num=0;
                cout<<"Enter task number to delete: ";
                cin>>num;
                t->deleteTask(num);
                continue;
            }
            else if (opt==4){
                opt=0;
                break;
            }
            opt=0;
        }
        //REWARD SHOP
        while(MenuOpt == 2){
            opt=t->printRewards();
            if (opt==1){
                //add task
                string inputReward;
                int inputVal=0;
                cout<<"Enter new reward: ";
                cin.ignore();
                getline(cin,inputReward);
                cout<<"Enter point value: ";
                cin>>inputVal;
                t->addReward(inputReward,inputVal);
                continue;
            }
            else if (opt==2){
                //delete task, subtract from points
                int num=0;
                cout<<"Enter reward number to purchase: ";
                cin>>num;
                int val=0;
                val = t->purchase(num);
                if (val== -1){
                    cout<<"Not enough points! Press any key to continue"<<endl;
                    cin>>num;
                }
                continue;
            }
            else if (opt==3){
                //delete task
                int num=0;
                cout<<"Enter reward number to delete: ";
                cin>>num;
                t->deleteReward(num);
                continue;
            }
            else if (opt==4){
                opt=0;
                break;
            }
            opt=0;
        }
    }
    //save function for tasks
    remove("tasks.txt");
    ofstream tfile("tasks.txt");
    int listsize = t->taskList.size();
    for(int i=0;i<listsize;i++){
        tfile<<t->taskList.front();
        t->taskList.pop_front();
    }
    tfile.close();
    //cout<<"Tasks saved";
    //save function for rewards
    remove("rewards.txt");
    ofstream rfile("rewards.txt");
    int rsize = t->rewardList.size();
    for(int i=0;i<rsize;i++){
        rfile<<t->rewardList.front();
        t->rewardList.pop_front();
    }
    rfile.close();
    //save points
    remove("pt.txt");
    ofstream log2("pt.txt");
    log2<<t->totalPoints<<endl;
    log2.close();
    return 0;
}