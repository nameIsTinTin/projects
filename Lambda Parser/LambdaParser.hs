{-# LANGUAGE InstanceSigs #-}
module LambdaParser where
import Parser
import Data.Lambda
import Data.Builder


-- You can add more imports if you need them

-- Remember that you can (and should) define your own functions, types, and
-- parser combinators. Each of the implementations for the functions below
-- should be fairly short and concise.


{-|
    Part 1
    <longLambdaP> ::= <startNew> | <startNewBrackets> 
    <startNew> ::= "\\" <expr2> <application>
    <startNewBrackets> ::= "(\\" <expr2> <application> ")" 
    <application> ::= "." <expr2_new> | "." <startNewBrackets>
    <expr2_new> ::= "(" <moreApplication> ")" | <moreApplication>
    <moreApplication> ::= "(" <expr2> ")" | <expr2> | <moreApplication> <moreApplication>
    <expr2> ::= [a-z] <expr2> | [a-z]

    -- long form - only 1 letter between lambda and dot such as \x.\y.\z
    -- short form - multiple such as \xyz.xyz

Just for part 1 -> \x (only one char after lambda) '.' 
-}

digit :: Parser Char
digit = is '0' ||| is '1' ||| is '2' ||| is '3' ||| is '4' ||| is '5' ||| is '6' ||| is '7' ||| is '8' ||| is '9'

expr1 :: Parser Char
expr1 = expr2 

expr2 :: Parser Char 
expr2 = oneof ['a'..'z']


-- | Exercise 1

-- | Parses a string representing a lambda calculus expression in long form
--
-- >>> parse longLambdaP "(λx.xx)"
-- Result >< \x.xx
--
-- >>> parse longLambdaP "(λx.(λy.xy(xx)))"
-- Result >< \xy.xy(xx)
--
-- >>> parse longLambdaP "(λx(λy.x))"
-- UnexpectedChar '('



-- build $ 'x' `lam` term 'x' `ap` term 'x' generates \x.xx

longLambdaP :: Parser Lambda
longLambdaP = (<$>) build startNew  ||| (<$>) build startNewBrackets

startNew :: Parser Builder
startNew =  
     do 
    _ <- is 'λ' 
    a <- expr2 
    b <- application
    pure(a `lam` b)

startNewBrackets :: Parser Builder 
startNewBrackets =
    do
   _ <- is '('
   _ <- is 'λ' 
   a <- expr2
   b <- application
   _ <- is ')' 
   pure (a `lam` b)

application :: Parser Builder 
application = do 
    _ <- is '.'
    expr2_new ||| startNewBrackets 
    

expr2_new :: Parser Builder 
expr2_new =  do
    _ <- is '('
    lst <- list1 moreApplication
    let first = foldl1 ap lst 
    _ <- is ')'
    pure first
 |||
    do
    lst <- list1 moreApplication
    let first = foldl1 ap lst 
    pure first

moreApplication :: Parser Builder 
moreApplication = do 
    _ <- is '(' 
    lst <- list1 ((<$>) term expr2)
    let first = foldl1 ap lst 
    _ <- is ')' 
    pure first 
    ||| 
    do 
    lst <- list1 ((<$>) term expr2)
    let first = foldl1 ap lst 
    pure first
    
-- | Parses a string representing a lambda calculus expression in short form
--
-- >>> parse shortLambdaP "λx.xx"
-- Result >< \x.xx
--
-- >>> parse shortLambdaP "λxy.xy(xx)"
-- Result >< \xy.xy(xx)


-- >>> parse shortLambdaP "λx.x(λy.yy)"
-- Result >< \x.x\y.yy
--
-- >>> parse shortLambdaP "(λx.x)(λy.yy)"
-- Result >< (\x.x)\y.yy

-- >>> parse shortLambdaP "λxyz"
-- UnexpectedEof
-- >>> parse shortLambdaP "(λx.x)λy.yy"
-- Result >< (\x.x)\y.yy
-- 
-- >>> parse shortLambdaP "(λx.x)(λy.y)(λx.xx)"
-- Result >< (\x.x)(\y.y)\x.xx
--
-- >>> parse shortLambdaP "λx.xλy.yλz.zz"
-- Result >< \x.x\y.y\z.zz

shortLambdaP :: Parser Lambda
shortLambdaP = (<$>) build shortStart 

shortStart :: Parser Builder
shortStart = do
   _ <- is 'λ' 
   moreShortStart

   ||| do 
   lst <- list1 checker
   let b = foldl1 ap lst
   pure(b)

   

checker :: Parser Builder 
checker =
    do
   _ <- is '(' 
   _ <- is 'λ'
   a <- moreShortStart
   _ <- is ')'
   pure a
   ||| 
   do
   _ <- is 'λ'
   moreShortStart


moreShortStart :: Parser Builder
moreShortStart = do
   a <- expr2
   b <- moreShortStart ||| shortExpr ||| shortExpr3
   _ <- is '.'
   pure (a `lam` b)
   ||| do 
   a <- expr2 
   _ <- is '.' 
   b <- moreShortStart ||| shortExpr ||| shortExpr3
   pure(a `lam` b)


shortExpr :: Parser Builder
shortExpr = do

    
    lst <- list1 ((<$>) term expr2)
    let first = foldl1 ap lst 
    second <- shortExpr2 ||| shortStart
    pure (first `ap` second)

    ||| 

    do 
    
    lst <- list1 ((<$>) term expr2)
    let first = foldl1 ap lst 
    pure first

shortExpr2 :: Parser Builder 
shortExpr2 = do 
    _ <- is '('
    first <- shortStart ||| shortExpr3
    _ <- is ')'
    pure first
   
    
shortExpr3 :: Parser Builder 
shortExpr3 = do 
    lst <- list1 ((<$>) term expr2)
    let first = foldl1 ap lst 
    pure first
    
   



    

-- | Parses a string representing a lambda calculus expression in short or long form
-- >>> parse lambdaP "λx.xx"
-- Result >< \x.xx
--
-- >>> parse lambdaP "(λx.xx)"
-- Result >< \x.xx
--
-- >>> parse lambdaP "λx..x"
-- UnexpectedChar '.'
--

lambdaP :: Parser Lambda
lambdaP = longLambdaP ||| shortLambdaP


{-|
    Part 2
-}

-- | Exercise 1

-- IMPORTANT: The church encoding for boolean constructs can be found here -> https://tgdwyer.github.io/lambdacalculus/#church-encodings

-- | Parse a logical expression and returns in lambda calculus
-- >>> lamToBool <$> parse logicP "True and False"
-- Result >< Just False
--
-- >>> lamToBool <$> parse logicP "True and False or not False and True"
-- Result >< Just True
--
-- >>> lamToBool <$> parse logicP "not not not False"
-- Result >< Just True
--
-- >>> parse logicP "True and False"
-- Result >< (\xy.(\btf.btf)xy\_f.f)(\t_.t)\_f.f
--
-- >>> parse logicP "not False"
-- Result >< (\x.(\btf.btf)x(\_f.f)\t_.t)\_f.f
-- >>> lamToBool <$> parse logicP "if True and not False then True or True else False"
-- Result >< Just True

-- IF = λbtf.b t f
-- AND = λxy. IF x  y FALSE
-- OR = λxy. IF x TRUE y 
-- NOT = λx. IF x FALSE TRUE


logicTrue :: Parser Builder
logicTrue = do 
    _ <- spaces 
    _ <- string "True" 
    _ <- spaces 
    pure (boolToLam True)


logicFalse :: Parser Builder
logicFalse  = do
        _ <- spaces 
        _ <- string "False" 
        _ <- spaces 
        pure (boolToLam False)

shortcutAnd :: Builder 
shortcutAnd = 'x' `lam` 'y' `lam` ('b' `lam` 't' `lam` 'f' `lam` term 'b' `ap` term 't' `ap` term 'f') `ap`
                             term 'x' `ap` term 'y' `ap` 
                             boolToLam False

logicAnd :: Parser Builder
logicAnd = do 
    _ <- spaces
    _ <- string "and" 
    _ <- spaces
    pure shortcutAnd  
              
logicIf :: Parser Builder 
logicIf = do
    _ <- spaces 
    _ <- string "if" 
    _ <- spaces    
    pure ('b' `lam` 't' `lam` 'f' `lam` term 'b' `ap` term 't' `ap` term 'f')


logicOr :: Parser Builder 
logicOr = do
    _ <- spaces 
    _ <- string "or" 
    _ <- spaces 
    pure ('x' `lam` 'y' `lam` ('b' `lam` 't' `lam` 'f' `lam` term 'b' `ap` term 't' `ap` term 'f') `ap`
                             term 'x' `ap` boolToLam True `ap` term 'y')
                

shortcutNot :: Builder 
shortcutNot = 'x' `lam` ('b' `lam` 't' `lam` 'f' `lam` term 'b' `ap` term 't' `ap` term 'f') `ap`
                             term 'x' `ap` boolToLam False `ap` boolToLam True

logicNot :: Parser Builder 
logicNot = do
    _ <- spaces 
    _ <- string "not" 
    _ <- spaces 
    pure shortcutNot


logicP :: Parser Lambda
logicP = (<$>) build logicChoice


logicChoice :: Parser Builder 
logicChoice = do  
    a <- logicTrue ||| logicFalse ||| logicNegation
    b <- logicAnd ||| logicOr 
    c <- logicChoice ||| logicTrue ||| logicFalse ||| logicNegation 
    pure (b `ap` a `ap` c)

    ||| do logicNegation
    ||| do logicConditions
    ||| do logicTrue ||| logicFalse
    
     
logicNegation :: Parser Builder 
logicNegation = do 
    a <- list1 logicNot 
    b <- logicTrue ||| logicFalse 
    let c = foldr ap b a 
    pure c

logicConditions :: Parser Builder 
logicConditions = do 
    a <- logicIf
    b <- logicChoice
    _ <- string "then" 
    c <- logicChoice 
    _ <- string "else" 
    d <- logicChoice
    pure (a `ap` b `ap` c `ap` d)


-- | Exercise 2

-- | The church encoding for arithmetic operations are given below (with x and y being church numerals)

-- | x + y = add = λxy.y succ x
-- | x - y = minus = λxy.y pred x
-- | x * y = multiply = λxyf.x(yf)
-- | x ** y = exp = λxy.yx

-- | The helper functions you'll need are:
-- | succ = λnfx.f(nfx)
-- | pred = λnfx.n(λgh.h(gf))(λu.x)(λu.u)
-- | Note since we haven't encoded negative numbers pred 0 == 0, and m - n (where n > m) = 0

-- | Parse simple arithmetic expressions involving + - and natural numbers into lambda calculus


-- >>> lamToInt <$> parse basicArithmeticP "5 + 4"
-- Result >< Just 9
--
-- >>> lamToInt <$> parse basicArithmeticP "5 + 9 - 3 + 2"
-- Result >< Just 13


lambdaSucc :: Builder 
lambdaSucc = 'n' `lam` 'f' `lam` 'x' `lam` term 'f' `ap` (term 'n' `ap` term 'f' `ap` term 'x')

lambdaPred :: Builder 
lambdaPred = 'n' `lam` 'f' `lam` 'x'` lam` term 'n' `ap` ('g' `lam` 'h' `lam` term 'h' `ap` (term 'g' `ap` term 'f')) `ap` 
              ('u' `lam` term 'x') `ap` ('u' `lam` term 'u')

number :: Parser Builder 
number = do intToLam <$> int

add :: Builder 
add = 'x' `lam` 'y' `lam` term 'y' `ap` lambdaSucc `ap` term 'x'
-- | x + y = add = λxy.y succ x

plus :: Builder -> Builder -> Builder
plus a b = add `ap` a `ap` b

lambdaAdd :: Parser (Builder -> Builder -> Builder)
lambdaAdd = do 
    _ <- spaces 
    _ <- is '+'
    _ <- spaces
    pure plus 
    
deduct :: Builder 
deduct = 'x' `lam` 'y' `lam` term 'y' `ap` lambdaPred `ap` term 'x'
-- | x - y = minus = λxy.y pred x

minus :: Builder -> Builder -> Builder
minus a b = deduct `ap` a `ap` b 

lambdaMinus :: Parser (Builder -> Builder -> Builder)
lambdaMinus = do 
    _ <- spaces 
    _ <- is '-'
    _ <- spaces 
    pure minus
    

basicArithmeticP :: Parser Lambda
basicArithmeticP = (<$>) build basicLambdaArithmetic

basicLambdaArithmetic :: Parser Builder 
basicLambdaArithmetic = chain number (lambdaAdd ||| lambdaMinus)

     
-- | Parse arithmetic expressions involving + - * ** () and natural numbers into lambda calculus
-- >>> lamToInt <$> parse arithmeticP "5 + 9 * 3 - 2**3"
-- Result >< Just 24
--
-- >>> lamToInt <$> parse arithmeticP "100 - 4 * 2**(4-1)"
-- Result >< Just 68


times :: Builder 
times = 'x' `lam` 'y' `lam` 'f' `lam` term 'x' `ap` (term 'y' `ap` term 'f')
-- | x * y = multiply = λxyf.x(yf)

multiply :: Builder -> Builder -> Builder
multiply a b = times `ap` a `ap` b

lambdaMultiply :: Parser (Builder -> Builder -> Builder)
lambdaMultiply = do 
    _ <- spaces 
    _ <- is '*'
    _ <- spaces
    pure multiply
    

power :: Builder 
power = 'x' `lam` 'y' `lam` term 'y' `ap` term 'x'

exponented :: Builder -> Builder -> Builder
exponented a b = power `ap` a `ap` b 
-- | x ** y = exp = λxy.yx

lambdaExp :: Parser (Builder -> Builder -> Builder)
lambdaExp = do 
    _ <- spaces 
    _ <- is '*'
    _ <- is '*'
    _ <- spaces 
    pure exponented


lambdaBracket :: Parser Builder 
lambdaBracket = do 
    _ <- spaces 
    _ <- is '('
    _ <- spaces
    a <- complexLambdaArithmetic
    _ <- spaces 
    _ <- is ')'
    _ <- spaces
    pure a
    
arithTerm0 :: Parser Builder 
arithTerm0 = lambdaBracket ||| number

arithTerm1 :: Parser Builder 
arithTerm1 = chain arithTerm0 lambdaExp

arithTerm2 :: Parser Builder
arithTerm2 = chain arithTerm1 lambdaMultiply

arithTerm3 :: Parser Builder 
arithTerm3 = chain arithTerm2 (lambdaAdd ||| lambdaMinus)


arithmeticP :: Parser Lambda 
arithmeticP = (<$>) build complexLambdaArithmetic

complexLambdaArithmetic :: Parser Builder 
complexLambdaArithmetic = do arithTerm3


-- | Exercise 3

-- | The church encoding for comparison operations are given below (with x and y being church numerals)

-- | x <= y = LEQ = λmn.isZero (minus m n)
-- | x == y = EQ = λmn.and (LEQ m n) (LEQ n m)

-- | The helper function you'll need is:
-- | isZero = λn.n(λx.False)True

-- >>> lamToBool <$> parse complexCalcP "9 - 2 <= 3 + 6"
-- Result >< Just True
--
-- >>> lamToBool <$> parse complexCalcP "15 - 2 * 2 != 2**3 + 3 or 5 * 3 + 1 < 9"
-- Result >< Just False

-- LEQ :: Parser Builder 
-- LEQ = 'm' `lam` 'n' `lam` term 

isZero :: Builder
isZero = 'n' `lam` term 'n' `ap` ('x' `lam` boolToLam False) `ap` boolToLam True

leq :: Builder 
leq = 'm' `lam` 'n' `lam` isZero `ap` (deduct `ap` term 'm' `ap` term 'n')

eq :: Builder 
eq = 'm' `lam` 'n' `lam` shortcutAnd `ap` (leq `ap` term 'm' `ap` term 'n') `ap` (leq `ap` term 'm' `ap` term 'n')

complexCalcP :: Parser Lambda
complexCalcP = (<$>) build builderComplexCalc

builderComplexCalc :: Parser Builder 
builderComplexCalc = do 
    a <- lambdaComplexCalc
    _ <- spaces 
    b <- logicOr
    _ <- spaces 
    c <- builderComplexCalc ||| lambdaComplexCalc
    pure(b `ap` a `ap` c)

    ||| do 
    a <- lambdaComplexCalc
    _ <- spaces 
    b <- logicAnd
    _ <- spaces 
    c <- builderComplexCalc ||| lambdaComplexCalc
    pure(b `ap` a `ap` c)

    ||| do lambdaComplexCalc

lambdaComplexCalc :: Parser Builder
lambdaComplexCalc = do 
    a <- complexLambdaArithmetic 
    _ <- spaces
    _ <- string "<=" ||| string "<"
    _ <- spaces
    b <- complexLambdaArithmetic
    pure(leq `ap` a `ap` b)

    ||| do
    a <- complexLambdaArithmetic 
    _ <- spaces
    _ <- string "!=" 
    _ <- spaces
    b <- complexLambdaArithmetic
    pure(shortcutNot `ap` (eq `ap` a `ap` b))

    ||| do 
    a <- complexLambdaArithmetic 
    _ <- spaces
    _ <- string ">=" ||| string ">"
    _ <- spaces
    b <- complexLambdaArithmetic
    pure(leq `ap` b `ap` a)

    ||| do
    a <- complexLambdaArithmetic 
    _ <- spaces
    _ <- string "==" 
    _ <- spaces
    b <- complexLambdaArithmetic
    pure(eq `ap` a `ap` b)



{-|
    Part 3
-}

-- | Exercise 1

-- | The church encoding for list constructs are given below
-- | [] = null = λcn.n
-- | isNull = λl.l(λht.False) True
-- | cons = λhtcn.ch(tcn)
-- | head = λl.l(λht.h) False
-- | tail = λlcn.l(λhtg.gh(tc))(λt.n)(λht.t)
--
-- >>> parse listP "[]"
-- Result >< \cn.n
--
-- >>> parse listP "[True]"
--Result >< (\htcn.ch(tcn))(\t_.t)\cn.n

--
-- >>> parse listP "[0, 0]"
-- Result >< (\htcn.ch(tcn))(\fx.x)((\htcn.ch(tcn))(\fx.x)\cn.n)
--
-- >>> parse listP "[0, 0"
-- UnexpectedEof

lambdaNull :: Builder 
lambdaNull = 'c' `lam` 'n' `lam` term 'n' 
lambdaIsNull :: Builder 
lambdaIsNull = 'l' `lam` term 'l' `ap` ('h' `lam` 't' `lam` boolToLam False) `ap` boolToLam True
lambdaCons :: Builder 
lambdaCons = 'h' `lam` 't' `lam` 'c' `lam` 'n' `lam` term 'c' `ap` term 'h' `ap` (term 't' `ap` term 'c' `ap` term 'n') 

lambdaHead :: Builder 
lambdaHead = 'l' `lam` term 'l' `ap` ('h' `lam` 't' `lam` term 'h') `ap` boolToLam False

lambdaTail :: Builder 
lambdaTail = 'l' `lam` 'c' `lam` 'n' `lam` term 'l' `ap` ('h' `lam` 't' `lam` 'g' `lam` term 'g' `ap` term 'h' `ap` (term 't' `ap` term 'c')) 
             `ap` ('t' `lam` term 'n') `ap` ('h' `lam` 't' `lam` term 't')


listP :: Parser Lambda
listP = (<$>) build lambdaListP 

lambdaListP :: Parser Builder 
lambdaListP = do 
    _ <- is '['
    a <- booleanListExtender
    _ <- is ']'
    pure a
    ||| do 
    _ <- is '['
    a <- intListExtender
    _ <- is ']'
    pure a
    ||| do 
    _ <- string "[]"
    pure lambdaNull


booleanListExtender :: Parser Builder 
booleanListExtender = do 
    a <- logicTrue ||| logicFalse 
    _ <- is ',' 
    b <- booleanListExtender ||| logicTrue ||| logicFalse
    pure (lambdaCons `ap` a `ap` b)

    ||| do 
    a <- logicTrue ||| logicFalse
    pure(lambdaCons `ap` a `ap` lambdaNull)

intListExtender :: Parser Builder 
intListExtender = do 
    a <- number
    _ <- is ',' 
    b <- intListExtender ||| number
    pure (lambdaCons `ap` a `ap` b)

    ||| do 
    a <- number
    pure(lambdaCons `ap` a `ap` lambdaNull)


    

-- >>> lamToBool <$> parse listOpP "head [True, False, True, False, False]"
-- Result >< Just True
--
-- >>> lamToBool <$> parse listOpP "head rest [True, False, True, False, False]"
-- Result >< Just False
--
-- >>> lamToBool <$> parse listOpP "isNull []"
-- Result >< Just True
--
-- >>> lamToBool <$> parse listOpP "isNull [1, 2, 3]"
-- Result >< Just False
listOpP :: Parser Lambda
listOpP = (<$>) build lambdaListOp

lambdaListOp :: Parser Builder
lambdaListOp = do 
    a <- list1 lambdaListOpTerms 
    b <- lambdaListP 
    let c = foldr ap b a
    pure c

lambdaListOpTerms :: Parser Builder 
lambdaListOpTerms = do 
    _ <- string "head" 
    _ <- spaces 
    pure lambdaHead 

    ||| do 
    _ <- string "rest" 
    _ <- spaces
    pure lambdaTail 

    ||| do 
    _ <- string "isNull"
    _ <- spaces 
    pure lambdaIsNull
   
   ||| do 
   _ <- string "cons"
   _ <- spaces 
   a <- number ||| logicTrue ||| logicFalse
   _ <- spaces 
   pure (lambdaCons `ap` a)

   ||| do 
   _ <- string "null"
   _ <- spaces 
   pure lambdaNull
    


-- | Exercise 2

-- | Implement your function(s) of choice below!

chain :: Parser a -> Parser (a -> a -> a) -> Parser a
chain p op = p >>= rest
 where
  rest a =
    (do
        f <- op
        b <- p
        rest (f a b)
      )
      ||| pure a

readInt :: String -> Maybe (Int, String)
readInt s = case reads s of
  [(x, rest)] -> Just (x, rest)
  _           -> Nothing

int :: Parser Int
int = P f
 where
  f "" = Error UnexpectedEof
  f x  = case readInt x of
    Just (v, rest) -> Result rest v
    Nothing        -> Error $ UnexpectedChar (head x)