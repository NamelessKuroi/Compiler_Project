
#ifndef SOURCEPOSITION_H_
#define SOURCEPOSITION_H_

class SourcePosition
{
    private:
        int start;
        int finish;
        int line;
    public:
      SourcePosition(int start, int finish, int line)
      {
        this->start = start;
        this->finish = finish;
        this->line = line;
      }

      int GetStart()
      {
          return start;
      }

      int GetFinish()
      {
        return finish;
      }

      int GetLine()
      {
        return line;
      }
};

#endif /* SOURCEPOSITION_H_ */
