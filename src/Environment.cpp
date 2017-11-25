#include "../include/Environment.h"
#include "../include/GlobalVariables.h"

Environment:: Environment(): fs(), commandsHistory() {}

void Environment:: start()
{
    string input="";
    string cmd;
    string content;
    while (input!="exit")
    {
        bool legal=false;
        cout << fs.getWorkingDirectory().getAbsolutePath() << ">";
        getline(cin,input);
        if (input!="exit") {
            int space = input.find(' ');
            if (space == -1) {
                cmd = input;
                content = "";
            } else {
                cmd = input.substr(0, space);
                content = input.substr(space + 1);
            }
            if (verbose==2 || verbose==3)
            {
                cout << input << endl;
            }
            if (cmd == "pwd") {
                PwdCommand * temp = new PwdCommand(content);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "cd") {
                CdCommand * temp = new CdCommand(content);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "ls") {
                LsCommand * temp= new LsCommand(content);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "mkdir") {
                MkdirCommand * temp = new MkdirCommand(content);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "mkfile") {
                MkfileCommand * temp = new MkfileCommand(content);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "cp") {
                CpCommand * temp = new CpCommand(content);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "mv") {
                MvCommand * temp = new MvCommand(content);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "rename") {
                RenameCommand * temp = new RenameCommand(content);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "rm") {
                RmCommand * temp = new RmCommand(content);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "history") {
                HistoryCommand * temp = new HistoryCommand(content, commandsHistory);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "verbose") {
                VerboseCommand * temp = new VerboseCommand(content);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (cmd == "exec") {
                ExecCommand * temp = new ExecCommand(content, commandsHistory);
                temp->execute(fs);
                addToHistory(temp);
                legal = true;
            }

            if (!legal) {
                ErrorCommand * temp = new ErrorCommand(input);
                temp->execute(fs);
                addToHistory(temp);
            }
        }

    }

}
 FileSystem& Environment:: getFileSystem()
{
    return fs;
}
void Environment:: addToHistory(BaseCommand *command)
{
    commandsHistory.push_back(command);
}
const vector<BaseCommand*>& Environment:: getHistory() const
{
    return commandsHistory;
}
void Environment:: clear()
{
    for (vector <BaseCommand*> :: iterator myIt = commandsHistory.begin(); myIt!=commandsHistory.end() ; myIt++)
    {
        delete (*myIt);
    }
    commandsHistory.clear();
}

Environment ::~Environment()
{
    clear();
}

Environment:: Environment(const Environment &other): fs(), commandsHistory()
{
    copy(other);
    fs = *(new FileSystem(other.fs));
}
Environment:: Environment(Environment &&other): fs(), commandsHistory() {
    commandsHistory = other.commandsHistory;
    fs = other.getFileSystem();
    other.commandsHistory.clear();
}

Environment & Environment :: operator=(const Environment &other)
{
    if(this != &other){
        clear();
        fs = other.fs;
        copy(other);

    }
    return *this;
}

Environment & Environment:: operator= ( Environment &&other)
{
    if(this != &other){
        clear();
        commandsHistory = other.commandsHistory;
        fs = other.fs;
        other.commandsHistory.clear();
    }
    return *this;
}

void Environment:: copy(const Environment &other)
{
    vector <BaseCommand*> :: const_iterator myIt;
    BaseCommand *copy;
    for(myIt = other.commandsHistory.begin();
        myIt != other.commandsHistory.end(); myIt++){
        string toCopy = (*myIt) -> toString();
        bool error=false;
        if(toCopy == "pwd"){
            copy = new PwdCommand((*myIt) -> getArgs());
            error=true;}
        if(toCopy == "cd"){
            copy = new CdCommand((*myIt) -> getArgs());
            error=true;}
        if(toCopy == "ls"){
            copy = new LsCommand((*myIt) -> getArgs());
            error=true;}
        if(toCopy == "mkdir"){
            copy = new MkdirCommand((*myIt) -> getArgs());
            error=true;}
        if(toCopy == "mkfile"){
            copy = new MkfileCommand((*myIt) -> getArgs());
            error=true;}
        if(toCopy == "cp"){
            copy = new CpCommand((*myIt) -> getArgs());
            error=true;}
        if(toCopy == "mv"){
            copy = new MvCommand((*myIt) -> getArgs());
            error=true;}
        if(toCopy == "rename"){
            copy = new RenameCommand((*myIt) -> getArgs());
            error=true;}
        if(toCopy == "rm"){
            copy = new RmCommand((*myIt) -> getArgs());
            error=true;}
        if(toCopy == "history"){
            copy = new HistoryCommand((*myIt) -> getArgs(), commandsHistory);
            error=true;}
        if(toCopy == "verbose"){
            copy = new VerboseCommand((*myIt) -> getArgs());
            error=true;}
        if(toCopy == "exec"){
            copy = new ExecCommand((*myIt) -> getArgs(), commandsHistory);
            error=true;}
        if (!error)
          copy = new ErrorCommand((*myIt) -> getArgs());

        commandsHistory.push_back(copy);
    }
}
