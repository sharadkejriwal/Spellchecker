// SPELL-CHECKER
//Sharad Kejriwal

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<fstream>
#include<regex>
#include<string>
#include<cstring>

using namespace std;


struct TSTnode
{
	char value;
	struct TSTnode *left;
	struct TSTnode *middle;
	struct TSTnode *right;
	bool end;
};

class Dictionary
{
	private:
		struct TSTnode *root=NULL;
	public :
	    Dictionary(){};
		void insert(char *str);
		struct TSTnode * createnode();
		int del(char *str){ del(str,root);};
		int del(char *str,struct TSTnode *ptr);
		int search(char *str);
		void traversal();
		void traverseutil(struct TSTnode *root,char *buffer,int depth);
};

struct TSTnode * Dictionary::createnode()
{
	struct TSTnode *k = new TSTnode;
	k->left=k->right=k->middle=NULL;
	k->end=false;
	return k;
}


void Dictionary::insert(char *str)
{
	int i=0;
	int symbol;
	struct TSTnode *k,*par;
	k=root;
	if(!root)
	{
		root=createnode();
		root->value=str[i];
		if(str[i+1]=='\0')
			root->end=true;
		i++;
		k=root->middle;
		par=root;
		symbol=0;
	}
	while(str[i]!='\0')
	{
		if(!k)
		{
			//cout << "INS ";
			if(symbol==0)
            {
                 par->middle=createnode();
                 k=par->middle;
            }
            else if(symbol==-1)
              {
                  par->left=createnode();
                  k=par->left;
              }
            else
               {
                   par->right=createnode();
                   k=par->right;
               }
			k->value=str[i];
			if(str[i+1]=='\0')
				k->end=true;
			i++;
			par=k;
			symbol=0;
			k=k->middle;
		}
		else if(k->value==str[i])
		{
			if(str[i+1]=='\0')
				k->end=true;
			i++;
			par=k;
			symbol=0;
			k=k->middle;
		}
		else if(str[i] < k->value)
		{
		    par=k;
		    symbol=-1;
			k = k->left;
		}
		else if(str[i] > k->value)
		{
		    par=k;
		    symbol=1;
			k = k->right;
		}
	}
}

int Dictionary::search(char *str)
{
    struct TSTnode *k;
    int i=0;
    k=root;
    while(str[i]!='\0')
    {
    	cout<<str[i] << " " ;
        if(!k)
         {
             cout << "Search unsuccessful\n";
             return 0;
             //break;
         }
        else if(str[i]==k->value)
        {
            if(str[i+1]=='\0' && k->end==true)
            {
                 cout << "Search successful\n";
                 return 1;
               //  break;
            }
            i++;
            k=k->middle;
        }
        else if(str[i]<k->value)
        {
            k=k->left;
        }
        else if(str[i]>k->value)
        {
            k=k->right;
        }
    }
    if(str[i]=='\0')
    {
    	cout << "HEllo ";
    	cout << "Search unsuccessful\n";
    	return 0;	
    } 
}

void Dictionary::traversal()
{
    char buffer[100];
    traverseutil(root,buffer,0);
}

void Dictionary::traverseutil(struct TSTnode *root,char *buffer,int depth)
{
    if(root)
    {
        traverseutil(root->left,buffer,depth);
        buffer[depth]=root->value;
        if(root->end==true)
        {
            buffer[depth+1]='\0';
            cout << buffer << "\n";
        }
        traverseutil(root->middle,buffer,depth+1);
        traverseutil(root->right,buffer,depth);
    }
}

int Dictionary::del(char *str,struct TSTnode *ptr)
{
    if(!ptr)
    {
        cout << "Search unsuccessful";
        return 0;
    }

    if(ptr->value==(*(str)))
    {
        if(*(str+1)=='\0')
        {
            if(ptr->value==(*str) && ptr->end==true)
            {
                if((!ptr->left)&&(!ptr->right)&&ptr->end==false)
                {
                    delete(ptr);
                    return 1;
                }
                else
                {
                    ptr->end=false;
                    return 0;
                }
            }
            else
            {
                cout << "Search unsuccessful";
                return 0;
            }
        }
        else if(del(str+1,ptr->middle)&&(!ptr->left)&&(!ptr->right))
        {
            delete(ptr);
            return 1;
        }
        else
            return 0;
    }
    else if((*str)<ptr->value)
    {
        del(str,ptr->left);
    }
    else if((*str)>ptr->value)
    {
        del(str,ptr->right);
    }
}


void check_file_for_spelling(Dictionary obj,char *file_name)
{
	string data;
	int i;
	char word_search[50];
	ifstream ifile;
	ifile.open(file_name);


	if(!ifile.is_open())			//checking for correct opening of file
	{
		cout << "Couldn't open file" << endl;
		return;
	}


	regex pat("[A-z]+");			//regular expression pattern ,pre-compile it not done yet


	while(!ifile.eof())
	{
		getline(ifile,data);
		smatch word;
		while (regex_search (data,word,pat)) 
		{
			i=0;
	    	for (auto x:word)
	    	{
	    		 smatch::iteartor it;
	    		 for(it=word.begin();it!=word.end();it++)
	    		 	cout << *it <<endl;
	    		// if(!obj.search(word_search))
	    		 //	cout << x << endl;
	    	}
	   		//std::cout << std::endl;
	   		data = word.suffix().str();
  		}
	}
}

void File_Handling(char *file_name)
{
	ifstream idict;
	char data[30],word[100];
	int i;
	Dictionary obj;

	// inserting dictionary words into Ternary search tree
	idict.open("dictionary.txt");
	/*while(!idict.eof())
	{
		idict.getline(data,30);
		obj.insert(data);
	}*/
	while(idict >> data)
	{
		obj.insert(data);
	}
	//obj.traversal();


	check_file_for_spelling(obj,file_name);
	/*ifile.open(file_name);
	if(!ifile.is_open())			//checking for correct opening of file
	{
		cout << "Couldn't open file" << endl;
		return;
	}
	// word[100];
	while(ifile >> word)
	{
		cout << word << " ";
		if(!obj.search(word))
			cout << word << endl;
	}
		/*for(i=0;i<10;i++)
	{
		//cin >> word;
		//obj.insert(word);
		cin >> word;
		obj.search(word);
	}*/
	// File spell checking
}


int main(int argc,char *argv[])
{
    int i;
	/*char str[100],str2[80],str3[800];
	Dictionary obj;
	for(i=0;i<10;i++)
    {
        cin>>str;
        obj.insert(str);
    }
	for(i=0;i<5;i++)
    {
      	cin>>str;
        obj.search(str);
    }
    cout << "\n\n";
	obj.traversal();
	for(i=0;i<5;i++)
    {
        cin>>str;
        obj.del(str);
    }
    cout << "\n\n";
    obj.traversal();*/
   File_Handling(argv[1]);
    return 0;
}
