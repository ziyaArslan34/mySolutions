/*
 * BallGames.cpp
 *
 *  Created on: Jan 4, 2021
 * 
 */

#include <array>
#include <iostream>
#include <cstdlib>
#include <random>
#include <unistd.h>
#include <memory>

static constexpr size_t STACKSIZE = 4;

static constexpr size_t BOXSIZE = 9;

class Stack
{
  std::array<int, STACKSIZE> m_arr;

  int m_top = 0;

  public:

    bool push(int num)
    {
      if(STACKSIZE == m_top)
      {
        return false;
      }
      m_arr[m_top++] = num;
      return true;
    }

    bool isEmpty() const
    {
      return (0 == m_top);
    }

    bool isFull() const
    {
      return (STACKSIZE == m_top);
    }

    bool isAllElementsAreSame() const
    {
      size_t result = 0;
      for (size_t i = 0; i < STACKSIZE; i++)
      {
        result ^= m_arr[i];
      }
      return (result == 0);
    }

    int pop()
    {
      if(0 == m_top)
      {
        return EXIT_FAILURE;
      }
      return m_arr[--m_top];
    }

    void print()
    {
      for(size_t index = 0; index < STACKSIZE; ++index)
      {
        if(0 == m_arr[index])
        {
          std::cout << "\e[94m";
        }
        else
        {
          std::cout << "\e[93m";
        }

        std::cout << m_arr[index] << "  " << "\n\n";
      }
    }
};

class Box
{
  Stack m_stack[BOXSIZE];

  bool isValidStack(const size_t index) const
  {
    return (index < BOXSIZE);
  }

  public:

    void initialize()
    {
      for(size_t boxIndex = 0; boxIndex < BOXSIZE ; ++boxIndex)
      {
        for(size_t stackIndex = 0; stackIndex < STACKSIZE ; ++stackIndex)
        {
          std::random_device rd;
          std::mt19937 gen(rd());
          std::uniform_int_distribution<> distrib(0, BOXSIZE - 1);
          m_stack[boxIndex].push(distrib(gen));
        }
      }
    }

    Stack* operator[](const size_t index)
    {
      if(!isValidStack(index))
      {
        return nullptr;
      }
      return &m_stack[index];
    }

    bool isFinished() const
    {
      size_t mood = 0;

      for(size_t stackIndex = 0; stackIndex < BOXSIZE ; ++stackIndex)
      {
        if(m_stack[stackIndex].isAllElementsAreSame())
        {
          mood++;
        }
      }

      std::cout << "\e[92mTamamlanan kutu : " << mood << std::endl;

      return (mood < 5);
    }

    bool isEmpty(const size_t index) const
    {
      if(isValidStack(index))
      {
        return m_stack[index].isEmpty();
      }
      return false;
    }

    bool isFull(const size_t index) const
    {
      if(isValidStack(index))
      {
        return m_stack[index].isFull();
      }
      return false;
    }

    int pop(const size_t index)
    {
      if(isValidStack(index))
      {
        return m_stack[index].pop();
      }
      return -1;
    }

    bool push(const size_t index, const size_t value)
    {
      if(isValidStack(index))
      {
        return m_stack[index].push(value);
      }
      return false;
    }

    void printAll()
    {
      for(size_t boxIndex = 0; boxIndex < BOXSIZE; ++boxIndex)
      {
        m_stack[boxIndex].print();
      }
    }
};

int main()
{
  Box boxInstance;

  boxInstance.initialize();

  int y;

  size_t x;

  std::cout << "\n\e[90mMerhaba ben ziya arslan bi oyun kodladim.Lutfen deneyin." << std::endl;
  std::cout << "\nOyuna hosgeldiniz.\nOyunun amaci 5 tane kutuyu ayni sayilarla doldurmaktir.\nKolay gelsin :)\n\n";

  while(boxInstance.isFinished())
  {
    boxInstance.printAll();

    std::cout << "\n\e[90mHangi kutudaki sayiyi alacaksin(1-9): ";
    
    std::cin >> x;

    if(x >= 1 && x <= 9)
    {
      if(boxInstance[x]->isEmpty())
      {
        std::cout << "\n\e[91mSectigin kutu bos!\n";
        continue;
      }
      else
      {
        y = boxInstance[x]->pop();
      }

      std::cout << "\nEldeki sayi >> " << y << "\n";

      std::cout << "\n\e[90mHangi kutuya koyacaksin(1-9): ";

      std::cin >> x;

      if(x >= 1 && x <= 9)
      {
        if(!boxInstance[x]->isFull())
        {
          boxInstance[x]->push(y);
        }
        else
        {
          std::cout << "\n\e[91mSectigin kutu dolu!\n";
        }
      }
      else
      {
        std::cout << "\n\e[91mLutfen (1-9) arasinda sayi girin!\n";
        sleep(1);
        continue;
      }
    }
    else
    {
      std::cout << "\n\e[91mLutfen (1-9) arasinda sayi girin!\n";
      sleep(1);
      continue;
    }
    system("clear");
  }

  system("clear");

  std::cout <<"\n\e[94mTEBRIKLER KAZANDINIZ...\n";

  return 0;
}
