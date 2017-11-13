#include "../include/Commands.h";

    BaseCommand:: BaseCommand(string args) : args(args) {}

    string BaseCommand:: getArgs()
    {
        return args;
    }

    PwdCommand:: PwdCommand(string args) : BaseCommand(args) {}
    void PwdCommand:: execute(FileSystem & fs)
    {
        return fs.getWorkingDirectory();
    }
    virtual string PwdCommand:: toString() { return "pwd"; }

    CdCommand:: CdCommand(string args) :BaseCommand(args) {}
    void execute(FileSystem & fs)
    {
        string sub;
        int i(0);
        bool loop=false;
        size_t found=args.find("/");
        if (found!=0 && found!=2)
        {
            cout << "The system cannot find the path specified";
            loop=true;
        }
        else {
            if (found == 0) {
                args = args.substr(1);
                found = args.find("/");
                if (found==-1)
                    sub=args;
                else
                    sub = args.substr(0, found);
            } else
                sub = args.substr(0, found);
        }
        while (!loop) {
            if (sub == "..") {
                if (fs.getWorkingDirectory().getParent() == nullptr)
                    cout << "The system cannot find the path specified";
                else
                    fs.setWorkingDirectory(fs.getWorkingDirectory().getParent());
            } else {
                vector<BaseFile *>::iterator myIt;
                bool found = false;
                for (myIt = fs.getWorkingDirectory().getChildren().begin();
                     myIt != fs.getWorkingDirectory().getChildren().end(); myIt++) {
                    if (sub.compare((**myIt).getName()) == 0) // ignored FILE
                    {
                        fs.setWorkingDirectory(**myIt);
                        found = true;
                    }
                }
                if (!found)
                    cout << "The system cannot find the path specified";
            }
            if (args==sub)
                loop=true;
            else
            args = args.substr(found + 1);
        }

    }
    string toString() {}



    LsCommand:: LsCommand(string args): BaseCommand(args) {}
    void execute(FileSystem & fs)
    {
        bool sortBySize=false;
        if (args.substr(0,4).compare("[-s]"==0))
        {
            sortBySize=true;
            args=args.substr(5);
        }

        Directory current = fs.getWorkingDirectory();
        while(args.size()>0)
        {
            size_t found=args.find("/");
            string sub;
            if (found == 0) {
                args = args.substr(1);
                found = args.find("/");
                if (found==-1)
                    sub=args;
                else
                    sub = args.substr(0, found);

            }
            else
            {
                if(args.substr(0,2).compare("..")!=0) {
                    cout << "The system cannot find the path specified";
                    args="";
                }

                else // it's ..
                {
                    current=current.*getParent();
                    args=args.substr(2);
                }

            }


        }


    }
    string toString() {}




