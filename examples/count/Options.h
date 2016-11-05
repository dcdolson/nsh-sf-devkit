#ifndef COUNT_OPTIONS_H
#define COUNT_OPTIONS_H

class CountOptions
{
public:
    CountOptions(int argc, char** argv);

    int GetIfIndex() const;

private:
    int m_ifIndex;
};

#endif

