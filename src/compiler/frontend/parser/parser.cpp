#include <iostream>

#include "parser.h"
#include "../scanner/scanner.h"
#include "../../token/token.h"  

using namespace std;

Parser::Parser(std::string filename)
{
    scanner = new Scanner(filename);
}

Parser::~Parser()
{
    delete scanner;
}

Node* Parser::parse()
{
    Node* root;
    token = scanner->read();
    root = program();
    if (token.is_eof()) {
        return root;
    }
    print_error_and_exit();
}

/**
 * <program> -> <vars> <block>
 */
Node* Parser::program()
{
    int level = 1;

    Node* node = Node::of(START, level);

    node->append_child(vars(level));
	
    node->append_child(block(level));
    return node;


}

/**
 * <block> -> begin <vars> <stats> end
 */
Node* Parser::block(int level)
{
    level++;
    
    if (KeywordToken::is_start_token(token)) {
        Node* node = Node::of(BLOCK, level);
        token = scanner->read();
        node->append_child(vars(level));
        node->append_child(stats(level));
        if (KeywordToken::is_end_token(token)) {
            token = scanner->read();
            return node;
        }
    }
    
    print_error_and_exit();
}

/**
 * <vars> -> var Identifier : Integer <vars> ; | empty
 */
Node* Parser::vars(int level)
{
	
    if (KeywordToken::is_var_token(token)) {
        level++;
        Node* node = Node::of(VARS, level);
        token = scanner->read();
        if (token.is_identifier()) {
            node->append_token(token);
            token = scanner->read();
            if (OperatorToken::is_equals_token(token)) {
            	node->append_token(token);
            	token = scanner->read();
            	if (token.is_integer()) {
            		node->append_token(token);
            		token = scanner->read();
            		if (OperatorToken::is_endline_token(token)) {
            			node->append_token(token);
            			token = scanner->read();
						node->append_child(vars(level));	
	            	    return node;
            		}
            	}
			}
            
            
        } else {
            print_error_and_exit();
        }
    } else {
        return NULL;
    }
}

/**
 * <exp> -> <A> ++ <exp> | <A>
 */
Node* Parser::expr(int level)
{
    level++;
    Node* node = Node::of(EXPR, level);
    node->append_child(A(level));
    if (OperatorToken::is_addition_token(token)) {
        node->append_token(token);
        token = scanner->read();
        node->append_child(expr(level));
        return node;
    }
    return node;
}

/**
 * <A> -> <N> -- <exp> | <N>
 */
Node* Parser::A(int level)
{
    level++;
    Node* node = Node::of(EXPR, level);
    node->append_child(N(level));
    if (OperatorToken::is_subtraction_token(token)) {
        node->append_token(token);
        token = scanner->read();
        node->append_child(expr(level));
        return node;
    }
    return node;
}

/**
 * <N> -> <M> / <N> | <M> * <N> | <M>
 */
Node* Parser::N(int level)
{
    level++;
    Node* node = Node::of(EXPR, level);
    node->append_child(M(level));
    
    if (OperatorToken::is_division_token(token)) {
    
	    node->append_token(token);
        token = scanner->read();
        node->append_child(N(level));
        return node;
    }
    if (OperatorToken::is_multiplication_token(token)) {
	    node->append_token(token);
        token = scanner->read();
        node->append_child(N(level));
        return node;
    }
    
    return node;
}

/**
 * <M> -> -- <M> | <R>
 */

Node* Parser::M(int level)
{
    level++;
    Node* node = Node::of(HASH, level);
    if (OperatorToken::is_negation_token(token)) {
        node->append_token(token);
        token = scanner->read();
        node->append_child(R(level));
        return node;
    } else {
        node->append_child(R(level));
        return node;
    }
    return node;
}

/**
 * <R> -> [ <expr> ] | Identifier | Integer
 */
Node* Parser::R(int level)
{
	
    level++;
    Node* node = Node::of(R_LETTER, level);
    if (DelimiterToken::is_left_square_bracket_token(token)) {
        token = scanner->read();
        node->append_child(expr(level));
        if (DelimiterToken::is_right_square_bracket_token(token)) {
            token = scanner->read();
            return node;
        }
    } else if (token.is_identifier()) {
        node->append_token(token);
        token = scanner->read();
        return node;
    } else if (token.is_integer()) {
        node->append_token(token);
        token = scanner->read();
        return node;
    }
    print_error_and_exit();
}

/**
 * <stats> -> <stat> <mStat>
 */
Node* Parser::stats(int level)
{
    level++;
    Node* node = Node::of(STAT, level);
    node->append_child(stat(level));
    node->append_child(mStat(level));
    return node;
}

/**
 * <mStat> -> empty | <stats>
 */
Node* Parser::mStat(int level)
{
    if (is_first_of_stats(token)) {
        level++;
        Node* node = Node::of(M_STAT, level);
        node->append_child(stats(level));
        return node;
    } else {
        return NULL;
    }
}

bool Parser::is_first_of_stats(Token token)
{
    return KeywordToken::is_read_token(token) ||
           KeywordToken::is_print_token(token) ||
           KeywordToken::is_start_token(token) ||
           KeywordToken::is_if_token(token) ||
           KeywordToken::is_iter_token(token) ||
           KeywordToken::is_let_token(token);
}

/**
 * <stat> -> <in> ; | <out> ; | <block> ; | <if> ; | <loop> ; | <assign> ;
 */
Node* Parser::stat(int level)
{
    level++;
    Node* node = Node::of(STAT, level);
    
    if (KeywordToken::is_read_token(token)) {
        node->append_child(in(level));
        check_for_semicolon_token();
        return node;
    } else if (KeywordToken::is_print_token(token)) {
        node->append_child(out(level));
        cerr<<"OK"<<endl;
        check_for_semicolon_token();
        return node;
    } else if (KeywordToken::is_start_token(token)) {
        node->append_child(block(level));
        check_for_semicolon_token();
        return node;
    } else if (KeywordToken::is_if_token(token)) {
        node->append_child(ifstat(level));
        check_for_semicolon_token();
        return node;
    } else if (KeywordToken::is_iter_token(token)) {
        node->append_child(loop(level));
        check_for_semicolon_token();
        return node;
    } else if (KeywordToken::is_let_token(token)) {
        node->append_child(assign(level));
        check_for_semicolon_token();
        return node;
    }
    print_error_and_exit();
}

void Parser::check_for_semicolon_token()
{
    if (DelimiterToken::is_semi_colon_token(token)) {
        token = scanner->read();
    } else {
        print_error_and_exit();
    }
}

/**
 * <in> -> read Identifier
 */
Node* Parser::in(int level)
{
	
    if (KeywordToken::is_read_token(token)) {
        level++;
        Node* node = Node::of(IN, level);
        token = scanner->read();
        if (token.is_identifier()) {
            node->append_token(token);
            token = scanner->read();
            return node;
        }
    }
    print_error_and_exit();
}

/**
 * <out> -> print ( <expr> )
 */
Node* Parser::out(int level)
{
    level++;
    if (KeywordToken::is_print_token(token)) {
        Node* node = Node::of(OUT, level);
        token = scanner->read();
        
        if (DelimiterToken::is_left_parentheses_token(token)) {
            token = scanner->read();
		
			node->append_child(expr(level));
		    if (DelimiterToken::is_right_parentheses_token(token)) {
        
		    	token = scanner->read();
            	return node;
            } else {
    			print_error_and_exit();        	
            }
        } else {
        	print_error_and_exit();	
        }
    }
    print_error_and_exit();
}

/**
 * <ifstat> -> if ( <expr> <O> <expr> ) <stat>
 */
Node* Parser::ifstat(int level)
{
    level++;
    if (KeywordToken::is_if_token(token)) {
        Node* node = Node::of(IFSTAT, level);
        token = scanner->read();
        if (DelimiterToken::is_left_parentheses_token(token)) {
            token = scanner->read();
            node->append_child(expr(level));
            node->append_child(O(level));
            node->append_child(expr(level));
            if (DelimiterToken::is_right_parentheses_token(token)) {
                token = scanner->read();
                node->append_child(stat(level));
                return node;
            }
        }
    }
    print_error_and_exit();
}

/**
 * <loop> -> iter ( <expr> <O> <expr> ) <stat>
 */
Node* Parser::loop(int level)
{
    level++;
    if (KeywordToken::is_iter_token(token)) {
        Node* node = Node::of(LOOP, level);
        token = scanner->read();
        if (DelimiterToken::is_left_parentheses_token(token)) {
            token = scanner->read();
            node->append_child(expr(level));
            node->append_child(O(level));
            node->append_child(expr(level));
            if (DelimiterToken::is_right_parentheses_token(token)) {
                token = scanner->read();
                node->append_child(stat(level));
                return node;
            }
        }
    }
    print_error_and_exit();
}

/**
 * <assign> -> let Identifier = <expr>
 */
Node* Parser::assign(int level)
{
    level++;
    if (KeywordToken::is_let_token(token)) {
        Node* node = Node::of(ASSIGN, level);
        token = scanner->read();
        if (token.is_identifier()) {
            node->append_token(token);
            token = scanner->read();
            if (OperatorToken::is_assignment_token(token)) {
                token = scanner->read();
                node->append_child(expr(level));
                return node;
            }
        }
    }
    print_error_and_exit();
}

/**
 * <O> -> < | > | :
 */
Node* Parser::O(int level)
{
    level++;
    Node* node = Node::of(OPERATOR, level);
    if (is_O_token(token)) {
        node->append_token(token);
        token = scanner->read();
        return node;
    }
    print_error_and_exit();
}

bool Parser::is_O_token(Token token)
{
    return OperatorToken::is_less_than_token(token) ||
           OperatorToken::is_greater_than_token(token) ||
           OperatorToken::is_equals_token(token);
}

void Parser::print_error_and_exit()
{
    std::cerr << "Parser print_error_and_exit: " << token << std::endl;
    exit(1);
}
