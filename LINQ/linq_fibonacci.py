from linq import Linq

def fibonacci_generator():
    a, b = 1, 1
    while True:
        yield a
        a, b = b, a + b

N = 10

def main():
    print(Linq(fibonacci_generator())
          .where(lambda x: x % 3 == 0)
          .select(lambda x: x if x % 2 else x ** 2)
          .take(N)
          .to_list())

if __name__ == '__main__':
    main()