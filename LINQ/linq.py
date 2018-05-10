from collections import defaultdict

class Linq:
    def __init__(self, iterable):
        self.iterable = iterable

    def flatten(self):

        def flatten_generator(iterable):
            for array in iterable:
                for x in array:
                    yield x

        return Linq(flatten_generator(self.iterable))

    def select(self, mapper_function):
        return Linq(map(mapper_function, self.iterable))

    def where(self, key_filter):
        return Linq(filter(key_filter, self.iterable))

    def take(self, n):

        def take_n_generator(iterable, n):
            i = 0
            for elem in iterable:
                if i == n:
                    break
                yield elem
                i += 1

        return Linq(take_n_generator(self.iterable, n))

    def group_by(self, key_function):

        dict_ = defaultdict(list)

        for x in self.iterable:
            dict_[key_function(x)].append(x)

        return Linq(dict_.items())

    def order_by(self, key_function):
        return Linq(sorted(self.iterable, key=key_function))

    def to_list(self):
        return list(self.iterable)

    def next(self):
        return self.iterable.next()

    def __iter__(self):
        return self.iterable.__iter__()