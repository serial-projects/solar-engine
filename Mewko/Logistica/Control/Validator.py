from datetime import datetime
import typing

class ValidatorContent:
    def __init__(self):
        self.code: int              = int(0)
        self.logs: typing.List[str] = list()
    
    def report_warn(self, message: str) -> None:
        __header: str = f'[Message] ({datetime.now().strftime("%H:%M:%S %d/%m/%Y")}): '
        self.logs.append(__header + message)
    
    def report_error(self, code: int, message: str) -> None:
        __header: str = f'[Error] ({datetime.now().strftime("%H:%M:%S %d/%m/%Y")}): '
        self.logs.append(__header + message)
        self.code = code

T = typing.TypeVar('T')
class Validator(typing.Generic[T]):
    def __init__(self, userdata: T):
        self.__userdata: T = userdata
        self.__at_error: typing.Optional[typing.Callable[[T, ValidatorContent], None]] = None
        self.__at_warn: typing.Optional[typing.Callable[[T, ValidatorContent], None]] = None
        self.content: ValidatorContent = ValidatorContent()
    
    def attach_error_callback(self, aterror: typing.Callable[[T, ValidatorContent], None]):
        self.__at_error = aterror
    
    def attach_warn_callback(self, atwarn: typing.Callable[[T, ValidatorContent], None]):
        self.__at_warn = atwarn
    
    def report_warn(self, message: str):
        self.content.report_warn(message)
        if self.__at_warn:
            self.__at_warn(self.__userdata, self.content)
    
    def report_error(self, message: str, code: int = 1): 
        self.content.report_error(code, message)
        if self.__at_error:
            self.__at_error(self.__userdata, self.content)