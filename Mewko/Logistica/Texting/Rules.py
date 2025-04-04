import typing
class Rules:
    def __init__(self):
        self.comment_token: int             = 0
        self.comment_line_hint: int         = 0
        self.comment_delimiter_starter: int = 0
        self.comment_delimiter_end: int     = 0
        self.rules: typing.Optional[typing.Callable[[int], int]] = None
    
    def set_comment_traps(
            self,
            token:              int,
            line_hint:          int,
            delimiter_starter:  int,
            delimiter_end:      int
        ):
        """An comment trap is basically the token the comment is made of."""
        self.comment_token = token
        self.comment_line_hint = line_hint
        self.comment_delimiter_starter = delimiter_starter
        self.comment_delimiter_end = delimiter_end
    
    def set_rules(self, rule: typing.Callable[[int], int]):
        """Set the rule function to decide the token."""
        self.rules = rule