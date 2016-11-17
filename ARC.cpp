//
//  arc.cpp
//  ARC
//
//  Created by Thamizharasan Rajendran on 11/26/15.
//  Copyright (c) 2015 Thamizharasan Rajendran. All rights reserved.
//

#include<iostream>
#include<string>
#include<stdlib.h>
#include<unordered_map>
#include<fstream>
#include<math.h>

using namespace std;
struct node
{
    node *next,*previous;
    int data;
};

class Doubly_linked_list
{ int count;
    int hit_count;
    int mis_count;
    node *head;
    node *tail;
public:
    Doubly_linked_list()
    {
        count=0;
        hit_count=0;
        mis_count=0;
        head=NULL;
        tail=NULL;
    }
    void numerator () {
        hit_count+=1;
    }
    int getnum() {
        return hit_count;
    }
    void misnumerator() {
        mis_count+=1;
    }
    int getmis() {
        return mis_count;
    }
    int getcount() {
        return count;
    }
    void printresult() {
        node *tmp=head;
        cout<<"\n";
        while (tmp!=NULL) {
            cout<<tmp->data<<"---->";
            tmp=tmp->next;
        }
        cout<<"NULL"<<'\n';
        
        node *tmp1=head;
        cout<<"\n";
        while (tmp1!=NULL) {
            cout<<tmp1<<"---->";
            tmp1=tmp1->next;
        }
        cout<<"NULL"<<'\n';
        
        
        
    }
    void switchtofront(node *t)
    {
        if(t==head)
        {
            return;
        }
        else {
            if(t->next==NULL)
            {
                tail=t->previous;
                t->previous->next=t->next;
                
                
            } else
            {
                t->previous->next=t->next;
                t->next->previous=t->previous;
                
            }
            t->previous=NULL;
            t->next=head;
            head->previous=t;
            head=t;
        }
    }
       int deletelastnode()
    {
        if(head==NULL)
        {
            return -1;
        }
        if(head==tail)
        {
            node *tmp=head;
            tail=NULL;
            head=NULL;
            int rtn_1=tmp->data;
            delete(tmp);
            count--;
            return rtn_1;
            
        }
        node *dln=tail;
        tail=dln->previous;
        tail->next=NULL;
        dln->previous=NULL;
        int rtrn_data=dln->data;
        delete(dln);
        count--;
        return rtrn_data;
    }
    
    void deletenode(int pg_no,node *ta)
    {
          if(head==NULL)
        {
            cout<<"inside firt"<<'\n';
            return -1;
        }
        else if(head==tail)
        {
            node *tmpa=head;
            tail=NULL;
            head=NULL;
            delete(tmpa);
            
        }
        else if (pg_no==tail->data){
            node *dlna=tail;
            tail=dlna->previous;
            tail->next=NULL;
            dlna->previous=NULL;
            delete(dlna);
            count--;
        }
        else
        {
            if(ta->previous!=NULL) {
             ta->previous->next=ta->next;
            ta->next->previous=ta->previous;
            ta->next=NULL;
            ta->previous=NULL;
            delete(ta);
            count--;
            } else {
            ta->next->previous=NULL;
            head=ta->next;
            delete(ta);
            count--;
            }
        }
    }
    
    
    node* insertfront(int pg_no)
    {
        node *newnode =new node;
        newnode->data=pg_no;
        newnode->previous=NULL;
        newnode->next=NULL;
        if(head!=NULL)
        {
            newnode->next=head;
            newnode->previous=NULL;
            head->previous=newnode;
            head=newnode;
        }
        else{
            head=newnode;
            tail=newnode;
        }
        count+=1;
        return head;
        
    }
};

class arc {
    int size_of_cache;
    int p;
    Doubly_linked_list T1;
    Doubly_linked_list B1;
    Doubly_linked_list T2;
    Doubly_linked_list B2;
    Doubly_linked_list a;
    unordered_map<int,node*> T1_hash;
    unordered_map<int,node*> T2_hash;
    unordered_map<int,node*> B1_hash;
    unordered_map<int,node*> B2_hash;
    
    
public:
    arc(int b) {
        int p=0;
      size_of_cache=b;
    }
    void request_pg(int pg_no)
    {    a.checksizes();
             unordered_map<int,node*>:: iterator T1_ord=T1_hash.find(pg_no);
        unordered_map<int,node*>:: iterator T2_ord=T2_hash.find(pg_no);
        unordered_map<int,node*>:: iterator B1_ord=B1_hash.find(pg_no);
        unordered_map<int,node*>:: iterator B2_ord=B2_hash.find(pg_no);
                if (T1_ord!=T1_hash.end()) {
                T1.deletenode(pg_no,((node *) T1_ord->second));
                T1_hash.erase(pg_no);
                node *newnode_T2= T2.insertfront(pg_no);
                T2_hash.insert(pair<int,node *>(pg_no,newnode_T2));
                    a.numerator();
                }
                else if (T2_ord!=T2_hash.end()) {
                    T2.switchtofront((node *) T2_ord->second);
                    a.numerator();
                    
                }
       // }
        else if(B1_ord!=B1_hash.end()) {
                 int P_del=0;
            if (B1_hash.size()>=B2_hash.size() || B1_hash.size()==0) {
                 P_del=1;
            } else
            {
                P_del=round(float(B2_hash.size())/float(B1_hash.size()));
            }
            int newp= p + P_del;
            if (newp < size_of_cache) {
                p=newp;
            }
            else{
                p=size_of_cache;
            }
            replace(pg_no,p);
            B1.deletenode(pg_no,((node *) B1_ord->second));
            B1_hash.erase(pg_no);
            node *newnode_T2= T2.insertfront(pg_no);
            T2_hash.insert(pair<int,node *>(pg_no,newnode_T2));
            a.misnumerator();
       }
        else if(B2_ord!=B2_hash.end()) {
            int P2_del=0;
            if (B2_hash.size()>=B1_hash.size() || B2_hash.size()==0) {
                P2_del=1;
            } else
            {
                P2_del=round(float(B1_hash.size())/float(B2_hash.size()));
            }
            int newp2=p-P2_del;
            if (newp2>0) {
                p=newp2;
            } else {
                p=0;
            }
          
            replace(pg_no,p);
            B2.deletenode(pg_no,((node *) B2_ord->second));
            B2_hash.erase(pg_no);
            node *newnode_T2= T2.insertfront(pg_no);
            T2_hash.insert(pair<int,node *>(pg_no,newnode_T2));
            a.misnumerator();
        
        }
        else {
            if ((T1_hash.size() + B1_hash.size())==size_of_cache) {
                if(T1_hash.size() < size_of_cache)
                {
                   int rtn_b1= B1.deletelastnode();
                    B1_hash.erase(rtn_b1);
                    replace(pg_no,p);
                } else {
                    int rtn_T1=T1.deletelastnode();
                     T1_hash.erase(rtn_T1);
                }
               }
            else if ((T1_hash.size() + B1_hash.size()) < size_of_cache) {
               if (T1_hash.size() + T2_hash.size() + B1_hash.size()+ B2_hash.size() >= size_of_cache) {
                  if ((T1_hash.size() + T2_hash.size() + B1_hash.size() + B2_hash.size())== 2*size_of_cache) {
                       int rtn_B2= B2.deletelastnode();
                       B2_hash.erase(rtn_B2);
                    }
                replace(pg_no,p);
                }
             }
            node *newnode_T1= T1.insertfront(pg_no);
            T1_hash.insert(pair<int,node *>(pg_no,newnode_T1));
            a.misnumerator();
        }
    }
    void replace(int pg_no,int p) {
        unordered_map<int,node*>:: iterator B2_ord=B2_hash.find(pg_no);
        if (!(T1_hash.empty()) && ( (T1_hash.size() > p) || (B2_ord!=B2_hash.end() && (T1_hash.size()==p)))){
            int rtn_T1 = T1.deletelastnode();
            T1_hash.erase(rtn_T1);
            node *newnode_B1= B1.insertfront(rtn_T1);
            B1_hash.insert(pair<int,node *>(rtn_T1,newnode_B1));
        } else
        {
            int rtn_T2=T2.deletelastnode();
            T2_hash.erase(rtn_T2);
            node *newnode_B2=B2.insertfront(rtn_T2);
            B2_hash.insert(pair<int,node *>(rtn_T2,newnode_B2));
            
        }
    }
    void printhitratio(int den) {
        int nu=a.getnum();
        int nu1=a.getnum();
        int miscnt=a.getmis();
        float final=float(nu)/float(den);
        float fin=((int)(final*10000))/100.0;
        cout<<"Hit ratio"<<" "<<fin<<'\n';
    }
    void checksizes()
    {
        if(  ((T1_hash.size()+T2_hash.size()) > 1024) || ((T1_hash.size()+T2_hash.size()+B1_hash.size()+B2_hash.size()) > 2048)) {
         //   if(  ((T1_hash.size()+T2_hash.size()) > 65536) || ((T1_hash.size()+T2_hash.size()+B1_hash.size()+B2_hash.size()) > 131072)) {
        cout<<"sum of T1 and T2"<<" "<<T2_hash.size()+T1_hash.size()<<'\n';
        cout<<"sum of all T1/T2/B1/B2"<<" "<<T1_hash.size()+T2_hash.size()+B1_hash.size()+B2_hash.size();
            exit(EXIT_FAILURE);
           // break;
         }
     }
};

int main(int argc, char *argv[]) {
    if(argc==3){
    int df=atoi(argv[1]);
        arc d(df);
        std::ifstream infile(argv[2]);
        int x,y;
        int z,m;
        int denom=0;
        int i =0;
        while(infile >> x >> y >> z >>m){
             denom+=y;
            for(i =x;i<(x+y);i++) {
            d.request_pg(i);
        }
       }
        d.printhitratio(denom);
    return 0;
} else {
        cout<<"Error: give 2 arguments separated by space"<<'\n';
        cout<<"example: *.cpp 1024 P4.lis"<<'\n';
        return 0;
    }
    
}




