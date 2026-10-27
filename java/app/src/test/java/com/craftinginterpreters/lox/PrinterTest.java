package com.craftinginterpreters.lox;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class PrinterTest {
    @Test public void PrinterSimple() {
        Expr expression = new Expr.Binary(new Expr.Unary(new Token(TokenType.MINUS, "-", null, 1), new Expr.Literal(123)), new Token(TokenType.STAR, "*", null, 1), new Expr.Grouping(new Expr.Literal(45.67)));

        AstPrinter printer = new AstPrinter();
        String outcome = printer.print(expression);

        assertEquals(outcome, "(* (- 123) (group 45.67))");
    }

    @Test public void PrinterRpn() {
        // uhhhh (1 + -2) * (4 -3)
        Expr expression = new Expr.Binary(new Expr.Grouping(new Expr.Binary(new Expr.Literal(1), new Token(TokenType.PLUS, "+", null, 1), new Expr.Unary(new Token(TokenType.MINUS, "-", null, 1), new Expr.Literal(2)))), new Token(TokenType.STAR, "*", null, 1), new Expr.Grouping(new Expr.Binary(new Expr.Literal(4), new Token(TokenType.MINUS, "-", null, 1), new Expr.Literal(3))));

        RpnPrinter printer = new RpnPrinter();
        String outcome = printer.print(expression);

        assertEquals(outcome, "1 2 ~- + 4 3 - *");
    }
    
}
