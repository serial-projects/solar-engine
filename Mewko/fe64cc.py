import typing

class Fe64CC:
    def __init__(self, progargs: typing.List[str]):
        self.progargs: typing.List[str] = progargs
    
    def run(self):
        pass

def app():
    import sys as __sys
    Fe64CC(__sys.argv).run()

if __name__ == '__main__':
    app()