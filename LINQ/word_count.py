from linq import Linq

N = 10

def main():
    with open("text.txt", "r") as file:
        #print(file.read())
        print(
            '\n'.join(
                Linq(file.readlines())
                    .select(lambda line: line.split())
                    .flatten()
                    .group_by(lambda word: word)
                    .select(lambda item: (item[0], len(item[1])))
                    .order_by(lambda item: -item[1])
                    .select(lambda item: item[0]+": "+str(item[1]))
                    .take(N)
                    .to_list())
            )

if __name__ == '__main__':
    main()