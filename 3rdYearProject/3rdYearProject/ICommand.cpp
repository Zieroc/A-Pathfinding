#ifndef ICOMMAND_H
#define ICOMMAND_H

class ICommand
{
public:
  virtual ~Command() {}
  virtual void execute() = 0;
};

#endif