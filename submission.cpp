#include <bits/stdc++.h>
using namespace std;

void getData(void);
class TimeStamp{

    public:

    string timestamp;

    void put(string timestamp1)
    {
        timestamp=timestamp1;
    }

    string gettimestamp()
    {
        return timestamp;
    }

};

struct MyGenesisNode{

 string name;
 string pass;
 string algo;
 float value;
};

struct ChildNode{

  TimeStamp timestamp;
  struct MyGenesisNode* data;
  unsigned int nNumber;
  unsigned int ChildNodeId;
  struct ChildNode *ref;
  vector<struct ChildNode*> child;
};

map<int,struct ChildNode*> all;

static int number=0;

string encryption(string value){
    char key ='H';
    string output = value;

    for (int i = 0; i < value.size(); i++)
        output[i] = value[i] ^ key;

    return output;
}

string timestamp()
{
     time_t tt;
    struct tm * ti;
    time (&tt);
    ti = localtime(&tt);

    return asctime(ti);
}

unsigned int unique()
{
    return rand();
}

void getData(int head,vector<struct ChildNode*> hChildNode)
{

    int size = hChildNode.size();
    string name,pass,algo="qwerty";
    float value;

    struct ChildNode *ChildNode1 = new ChildNode();
    struct MyGenesisNode *data1=new MyGenesisNode();
    string date = timestamp();
    TimeStamp time;
    time.put(date);
    ChildNode1->timestamp=time;
    cout<<"Enter Name:\n";
    cin>>name;
    data1->name=encryption(name);
    cout<<"Enter pass:\n";
    cin>>pass;
    data1->pass=encryption(pass);

    data1->algo=encryption(algo);
    cout<<"Enter value:\n";
    cin>>value;
    data1->value=value;

    ChildNode1->data=data1;
    ChildNode1->nNumber=++number;
    ChildNode1->ChildNodeId=unique();


    if(head==-1)
    {
        ChildNode1->ref=NULL;
        hChildNode.push_back(ChildNode1);
    }
    else
    {
        all[head]->child.push_back(ChildNode1);
        ChildNode1->ref=all[head];

    }

    all[number]=ChildNode1;
    return;
}

bool verification(string pass,string algo)
{
        string pass1=encryption(pass);
        string algo1=encryption("qwerty");

        map<int,struct ChildNode*>::iterator it=all.begin();
        int flag=0;

        for(;it!=all.end(); it++)
        {
            if(it->second->data->pass==pass1 && it->second->data->algo==algo1)
            {
                flag=1;
                cout<<encryption(it->second->data->name)<<endl;

                break;
            }
        }

        if(flag==1)
        return true;

        return false;
}

int c=0;

void longest(struct ChildNode* root,int &ma)
{
    	if(root==NULL)
            return;

 		   c++;

    		for(int i=0; i<root->child.size(); i++)
            {
                longest(root->child[i],ma);
            }

    	if(c>ma)
            ma=c;
}

void levels(struct ChildNode* root,int c,int &ma)
{
    	if(root==NULL)
            return;

    		for(int i=0; i<root->child.size(); i++)
            {
                levels(root->child[i],c+1,ma);
            }

    	if(c>ma)
            ma=c;
}

int main()
{
    vector<struct ChildNode *> hChildNode;


    while(1)
    {
		cout<<"1 : Create new ChildNode\n";
		cout<<"2 : Create multi-set from first ChildNode\n";
		cout<<"3 : Create new ChildNode to any set of ChildNode\n";
		cout<<"4 : encryption MyGenesisNode\n";
		cout<<"5 : verification Owner\n";
		cout<<"6 : Break ChildNode\n";
		cout<<"7 : Change Owner\n";
		cout<<"8 : Longest chain\n";
		cout<<"9 : Longest chain of Sub-ChildNode\n";
		cout<<"11 : Exit"<<endl;
		cout<<"* - * - * - * - * - *"<<endl<<endl;
        int num;
        cout<<"\nEnter choice:\n";
        cin>>num;


        if(num==11)
        break;



        if(num==1)
        {
            //cout<<"hi";
            getData(-1,hChildNode);
        }

        if(num==2)
        {
            cout<<"enter no. of sets\n";
            int sets;
            cin>>sets;

            while(sets--)
            {
                getData(-1,hChildNode);
            }
        }

        if(num==3)
        {
            int nNum;
            cout<<"enter ChildNode number";
            cin>>nNum;

            getData(nNum,hChildNode);
        }

        if(num==4)
        {
            string pass,algo;
            cout<<"Enter pass + encryptionion Key"<<endl;

            bool k=verification(pass,algo);
        }

        if(num==5)
        {
            string pass,algo;
            cout<<"Enter pass and algo key";

            bool k=verification(pass,algo);

            if(k)
            cout<<"Verified"<<endl;
            else
            cout<<"Not Verified"<<endl;

            cout<<endl;
        }

        if(num==6)
        {
            int nNum;
            cout<<"enter ChildNode number";
            cin>>nNum;
            all.erase(nNum);
        }

        if(num==7)
        {
            int nN1,nN2;
            cout<<"enter ChildNode number of first ChildNode and new owner";
            cin>>nN1>>nN2;

            struct ChildNode* first=all[nN1];
            struct ChildNode* newowner=all[nN2];

            first->ref->child.erase(first->child.begin()+nN1);
            newowner->child.push_back(first);
            first->ref=newowner;
        }

        if(num==8)
        {
            int ma=0;
            c=0;

            for(int i=0; i<hChildNode.size(); i++)
            	longest(hChildNode[i],ma);

            cout<<ma<<endl;
        }

    	if(num==9)
        {
            int ma=0;

            for(int i=0; i<hChildNode.size(); i++)
            	levels(hChildNode[i],0,ma);

            cout<<ma<<endl;
        }

        if(num==10)
        {
            int nN1,nN2;
            cout<<"Enter Numbers of 1 & 2";
            cin>>nN1>>nN2;

            struct ChildNode* first=all[nN1];
            struct ChildNode* second=all[nN2];

            merge(first,second,hChildNode);
        }

    }

   return 0;
}
