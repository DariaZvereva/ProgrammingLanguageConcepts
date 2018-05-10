from linq import Linq

def fibonacci_generator():
    a, b = 1, 1
    while True:
        #print(a)
        yield a
        a, b = b, a + b

N = 5 

def main():

    for i in Linq(fibonacci_generator()).take(5):
      print(i)

    # print(Linq(fibonacci_generator())
    #       .where(lambda x: x % 3 == 0)
    #       .select(lambda x: x ** 2 if x % 2 else x)
    #       .take(N)
    #       .to_list())

if __name__ == '__main__':
    main()