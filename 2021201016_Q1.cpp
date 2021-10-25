#include<bits/stdc++.h>
using namespace std;

struct Trie{

    struct Trie *arr[26];
    bool isEnd;
    string value;

};

struct Trie *makenode(void){

    struct Trie *temp = new Trie;

    for(int i=0;i<26;i++){
        temp->arr[i]=NULL;

    }
    temp->isEnd=false;
    return temp;
}

void insert(struct Trie *root,string word){
    struct Trie *temp=root;
    for(char c:word){
        if(temp->arr[c-'a']==NULL){         //if that char is not present
            temp->arr[c-'a']=makenode();
        }
        temp=temp->arr[c-'a'];      //pointing to next char
    }
    temp->value=word;
    temp->isEnd=true;         //word is present and has been came to end
}

    bool search(struct Trie *root,string word){
        struct Trie *temp=root;
        for(char c:word){
            if(temp->arr[c-'a']==NULL){
                return false;           //that entry is not present means that word is not present
            }
            temp=temp->arr[c-'a'];
        }
        if(temp->isEnd==false){     //the word is not ending
            return false;
        }
        return true;        //reached at end

    }

    void morewords(Trie *root,string key,vector<string> &dict){
        if(root->isEnd==true){
            dict.push_back(key);
        }
        int k;
        for(k=0;k<26;k++){
            if(root->arr[k]!=NULL){
                break;
            }
        }
        if(k==26){
            return;
        }
        for(int i=0;i<26;i++){
            if(root->arr[i]!=NULL){
                key.push_back('a'+i);
                morewords(root->arr[i],key,dict);
                key.pop_back();
            }
        }

    }

    void autocomplete(Trie *root,string key,vector<string> &dict){
        Trie *temp=root;

        for(int i=0;i<key.length();i++){
            if(temp->arr[key[i]-'a']==NULL){
                return;
            }
            temp=temp->arr[key[i]-'a'];

        }
        
        int k;
        for(k=0;k<26;k++){
            if(temp->arr[k]!=NULL){
                break;
            }
        }
        if(k==26){
            return;
        }
        morewords(temp,key,dict);

    }

    void autocorrect(Trie *root,string& word,vector<int> current_row,char c,vector<string> &result){
        int size=current_row.size();
        vector<int> next_row(size);
        next_row[0]=current_row[0]+1;
        int insert,dele,replace;
        for(int i=1;i<size;i++){
            insert=next_row[i-1]+1;
            dele=current_row[i]+1;
            int f=min(insert,dele);
            if(c==word[i-1]){
                replace=current_row[i-1];
            }else{
                replace=current_row[i-1]+1;
            }
            next_row[i]=min(replace,f);
        }
        if(next_row[size-1]<=3 && root->isEnd==true){
            result.push_back(root->value);
        }

        int min=*min_element(next_row.begin(),next_row.end());
        if(min<=3){
            for(int i=0;i<26;i++){
                if(root->arr[i]!=NULL){
                    char ch=i+'a';
                autocorrect(root->arr[i],word,next_row,ch,result);
                }
            }
        }
        



    }


    int main(){

        struct Trie *root=makenode();
        int n;
        cin>>n;
        vector<string> words(n);
        string s;
        for(int i=0;i<n;i++){
            cin>>s;
            words[i]=s;
        }
        
        for(int i=0;i<n;i++){
            insert(root,words[i]);
        }
        int test_case;
        cin>>test_case;
        if(test_case==1){
            string key;
            cin>>key;
            if(search(root,key)){
            cout<<1<<endl;

            }else{
                cout<<0<<endl;
            }
        }
        else if(test_case==2){
             vector<string> dict;
            string prefixword;
            cin>>prefixword;
            autocomplete(root,prefixword,dict);
            cout<<dict.size()<<endl;
            for(int i=0;i<dict.size();i++){
            cout<<dict[i]<<endl;
            } 

        }else if(test_case==3){
            vector<string> result;
            string auto_word;
            cin>>auto_word;
            int size=auto_word.length();
            vector<int> current_row(size+1);
            for(int i=0;i<size;i++){
            current_row[i]=i;
            }
            current_row[size]=size;
            for(int i=0;i<26;i++){
                if(root->arr[i]!=NULL){
                    char ch=i+'a';
                    autocorrect(root->arr[i],auto_word,current_row,ch,result);
                }
            }
            cout<<result.size()<<endl;
            for(int i=0;i<result.size();i++){
                cout<<result[i]<<endl;
            }

        }
        // string key;
        // cin>>key;
        // if(search(root,key)){
        //     cout<<1<<endl;

        // }else{
        //     cout<<0<<endl;
        // }

        // vector<string> dict;
        // string prefixword;
        //  prefixword="cat";
        // autocomplete(root,prefixword,dict);
        // for(int i=0;i<dict.size();i++){
        // cout<<dict[i]<<endl;
        // }  

        // vector<string> result;
        // string auto_word;
        // cin>>auto_word;
        // int size=auto_word.length();
        // vector<int> current_row(size+1);
        // for(int i=0;i<size;i++){
        //     current_row[i]=i;
        // }
        // current_row[size]=size;
        // for(int i=0;i<26;i++){
        //     if(root->arr[i]!=NULL){
        //             char ch=i+'a';
        //         autocorrect(root->arr[i],auto_word,current_row,ch,result);
        //     }
        // }
        // cout<<result.size()<<endl;
        // for(int i=0;i<result.size();i++){
        //     cout<<result[i]<<endl;;
        // }

        return 0;
    }