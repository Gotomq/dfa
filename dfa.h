#ifndef DFA_H
#define DFA_H

#include <bits/stdc++.h>
#define err -1

using namespace std;

class DFA
{
public:
    DFA(char *filename, string &chrs_) : file(filename),
                                         chrs(chrs_),
                                         ifl(0),
                                         curr_st(0)
    {
        if (!file.is_open())
            perror("error while loading file\n");
        parseValues();
        if (file.bad())
            perror("error while reading file\n");
        file.close();
    }
    void parseValues()
    {
        for (string ln; getline(file, ln); ++ifl)
        {
            stringstream iss(ln);
            string value;
            switch (ifl)
            {
            /* Getting rows and columns metavalues */
            case 0:
                for (int i = 0; getline(iss, value, 'x'); ++i)
                {
                    // cout << "[LINE " << ifl << "] Getting Rows&Columns values, Value->" << value << "\n";
                    if (i == 0)
                        dm[0] = stoi(value);
                    else
                        dm[1] = stoi(value);
                }
                break;
            /* Getting Accepted States */
            case 1:
                for (; getline(iss, value, ',');)
                {
                    // cout << "[LINE " << ifl << "] Getting AcceptedStates, Value->" << value << "\n";
                    accptSt.push_back(stoi(value));
                }
                break;
            /* Getting Alphabet , info given by n# columns */
            case 2:
                for (; getline(iss, value, ' ');)
                {
                    // cout << "[LINE " << ifl << "] Getting Alphabet, Value->'" << value << "'\n";
                    alphSt.push_back(value);
                }
                break;
            /* Filling transition table */
            default:
                int curr_col = 0;
                static int curr_rw = 0;
                tr_table.push_back(vector<int>());
                for (; getline(iss, value, ' ');)
                {
                    // cout << "[LINE " << ifl << "] Getting table,  Value->" << value << " Row->"<< curr_rw << " Column->"<< curr_col <<"\n";
                    tr_table[curr_rw].push_back(stoi(value));
                    curr_col++;
                }
                curr_rw++;
                break;
            }
        }
    }
    int isPartOf(string &chr)
    {
        // alphabet => "alpha",
        // digits => "digit",
        // other => is just a char '_'
        for (const string &alph : alphSt)
        {
            if (alph == "digit")
            {
                if (isdigit(chr.c_str()[0]))
                    return 1;
            }
            else if (alph == "alpha")
            {
                if (isalpha(chr.c_str()[0]))
                    return 1;
            }
            else if (chr == alph)
            {
                return 1;
            }
            else
                continue;
        }
        return 0;
    }
    int getColumn(char &chr)
    {
        int colIndex = 0;
        string chr_(&chr, 1);
        cout << "🔨 Analyzing '" << chr_ << "' ...\n";
        for (const string &i : alphSt)
        {
            cout << "🤔 checking if its->'" << i << "' \n";
            // cout << "yyyy " << (i == string(chr,1)) << "..."<< string(chr,1) << "\n";
            if (!isPartOf(chr_))
            {
                return -1;
            }
            else if (i == "digit")
            {
                if (isdigit(chr))
                {
                    cout << "✅ It's digit at alphabet[" << colIndex << "]\n";
                    return colIndex;
                } //else cout << "❌ It's not '"<< i <<"' at alphabet["<< colIndex << "]\n";
            }
            else if (i == "alpha")
            {
                if (isalpha(chr))
                {
                    cout << "✅ It's alphabet at alphabet[" << colIndex << "]\n";
                    return colIndex;
                } //else cout << "❌ It's not '"<< i <<"' at alphabet["<< colIndex << "]\n";
            }
            else if (i == chr_)
            {
                cout << "✅ It's '" << i << "' at alphabet[" << colIndex << "]\n";
                return colIndex;
            } //else cout << "❌ It's not '"<< i <<"' at alphabet["<< colIndex << "]\n";
            colIndex++;
        }
        return -1;
    }
    void vectorInfo()
    {
        cout << "<<< Vector info >>>\n";
        cout << "Vector Rows->" << tr_table.size() << "\n";
        cout << "Vector Columns->" << tr_table[0].size() << "\n";
        for (const auto &r : tr_table)
        {
            for (const auto &c : r)
                cout << c << "\t";
            cout << "\n";
        }
    }
    void alphabetInfo()
    {
        cout << "<<< Alphabet order >>>\n[";
        for (const string &i : alphSt)
        {
            cout << "'" << i << "' ";
        }
        cout << "]\n";
    }
    int isAccepted()
    {
        for (const int &it : accptSt)
        {
            if (curr_st == it)
                return 1;
        }
        return 0;
    }
    void testString()
    {
        for (char &ch : chrs)
        {
            int column = getColumn(ch);
            cout << column << "\n";
            if (column == err)
            {
                fprintf(stderr, "😥 Invalid character %c\n", ch);
                return;
            }
            curr_st = tr_table[curr_st][column];
            if (curr_st == err)
            {
                fprintf(stderr, "😥 Invalid character %c\n", ch);
                return;
            }
        }
        if (isAccepted())
        {
            cout << "😎 Valid string '" << chrs << "'\n";
        }
        else
        {
            cout << "😥 Invalid string '" << chrs << "'\n";
        }
    }

private:
    int dm[2];
    int ifl;             /* initialize at creation */
    vector<int> accptSt; // accepted states & alphabet
    vector<string> alphSt;
    vector<vector<int>> tr_table; //transition table
    ifstream file;
    string chrs;
    int curr_st;
};
#endif