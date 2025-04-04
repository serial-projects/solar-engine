import typing

class MewkoCC:
    def __init__(self, progargs: typing.List[str]):
        self.progargs: typing.List[str] = progargs
    
    def run(self):
        pass

def app():
    import sys as __sys
    MewkoCC(__sys.argv).run()

if __name__ == '__main__':
    app()