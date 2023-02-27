int main(){
    char *p = new char[100];
    delete [] p;
    p[0] = 'a';
}
