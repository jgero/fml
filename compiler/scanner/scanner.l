%{
%}

%%

"[" 	    	{return T_SQB_OPEN;}
"]" 	    	{return T_SQB_CLOSE;}
"." 	    	{return T_DOT;}
"[a-zA-Z]+" 	{return T_VALUE;}
\n	        	{return T_NEWLINE;}
.               { return T_ERROR; }

%%
