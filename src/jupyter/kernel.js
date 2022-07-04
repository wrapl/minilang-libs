"use strict";

/*
.cm-s-default .cm-keyword {color: #708;}
.cm-s-default .cm-atom {color: #219;}
.cm-s-default .cm-number {color: #164;}
.cm-s-default .cm-def {color: #00f;}
.cm-s-default .cm-variable,
.cm-s-default .cm-punctuation,
.cm-s-default .cm-property,
.cm-s-default .cm-operator {}
.cm-s-default .cm-variable-2 {color: #05a;}
.cm-s-default .cm-variable-3, .cm-s-default .cm-type {color: #085;}
.cm-s-default .cm-comment {color: #a50;}
.cm-s-default .cm-string {color: #a11;}
.cm-s-default .cm-string-2 {color: #f50;}
.cm-s-default .cm-meta {color: #555;}
.cm-s-default .cm-qualifier {color: #555;}
.cm-s-default .cm-builtin {color: #30a;}
.cm-s-default .cm-bracket {color: #997;}
.cm-s-default .cm-tag {color: #170;}
.cm-s-default .cm-attribute {color: #00c;}
.cm-s-default .cm-hr {color: #999;}
.cm-s-default .cm-link {color: #00c;}

.cm-s-default .cm-error {color: #f00;}
.cm-invalidchar {color: #f00;}
*/


define(function() {
	function onload() {
		console.log("Loading Minilang kernel.js")

		CodeMirror.defineMode("minilang", function () {
			const Keywords = {
				"_": true, "and": true, "case": true, "debug": true, "def": true, "do": true,
				"each": true, "else": true, "elseif": true, "end": true, "exit": true, "for": true,
				"fun": true, "if": true, "in": true, "is": true, "let": true, "loop": true,
				"meth": true, "must": true, "next": true, "nil": true, "not": true, "old": true,
				"on": true, "or": true, "ref": true, "ret": true, "susp": true, "switch": true,
				"then": true, "to": true, "until": true, "var": true, "when": true, "while": true,
				"with": true
			};

			const IdInit = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
			const IdChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";
			const Brackets = "(){}[]";
			const Symbols = "!$%^&*-+=@#~?\\/<>,|;.`";
			const Either = IdInit + Symbols + ":\"";

			function tokenMinilang(Stream, State) {
				if (Stream.match(/--/, true)) {
					Stream.skipToEnd();
					return "comment";
				}
				if (State.InsideString && Stream.eat("{")) {
					State.InsideString = false;
					State.BraceLevel += 1;
					return "bracket";
				}
				if (State.InsideString || Stream.eat("\'")) {
					while (true) {
						if (Stream.eat("\'")) {
							State.InsideString = false;
							return "string";
						}
						if (Stream.peek() === "{") {
							State.InsideString = true;
							return "string";
						}
						if (Stream.eat("\\")) {
							if (Stream.eat("x")) if (!Stream.next()) return "error";
							if (!Stream.next()) return "error";
						} else if (!Stream.next()) {
							State.InsideString = true;
							return "string";
						}
					}
				}
				if (Stream.match(/-=/, true)) {
					State.CommentLevel += 1;
					return "comment";
				}
				if (State.CommentLevel) {
					if (Stream.match(/=-/, true)) {
						State.CommentLevel -= 1;
					} else {
						Stream.next();
					}
					return "comment";
				}
				if (State.BraceLevel) {
					if (Stream.eat("}")) {
						State.BraceLevel -= 1;
						State.InsideString = true;
						return "bracket";
					}
				}
				if (Stream.eatSpace()) return null;
				if (Stream.match(/[0-9]+/, true)) {
					if (Stream.eat("_")) {
						Stream.match(/[0-9A-Za-z]+/, true);
						return "number";
					}
					if (Stream.eat(".")) {
						Stream.match(/[0-9]*/, true);
						if (Stream.eat(/[eE]/)) {
							Stream.eat(/[+-]/);
							if (Stream.match(/[0-9]+/, true)) return "number";
						}
					}
					return "number";
				}
				if (Stream.eat("\"")) {
					while (!Stream.eat("\"")) {
						if (Stream.eat("\\")) {
							if (Stream.eat("x")) if (!Stream.next()) return "error";
						}
						if (!Stream.next()) return "error";
					}
					return "string";
				}
				if (Stream.eat(":")) {
					if (Stream.eat("?")) return "atom";
					if (Stream.eat("\"")) {
						while (!Stream.eat("\"")) {
							if (Stream.eat("\\")) {
								if (Stream.eat("x")) if (!Stream.next()) return "error";
							}
							if (!Stream.next()) return "error";
						}
						return "atom";
					} else {
						Stream.match(/[A-Za-z_][0-9A-Za-z_]+/, true);
						return "atom";
					}
				}
				var Id = Stream.match(/[A-Za-z_][0-9A-Za-z_]+/, true);
				if (Id) {
					if (Id[0] in Keywords) return "keyword";
					return "identifier";
				}
				var C = Stream.peek();
				if (C) {
					if (Symbols.indexOf(C) >= 0) {
						Stream.next();
						return "operator";
					} else if (Brackets.indexOf(C) >= 0) {
						Stream.next();
						return "bracket";
					}
				}
				Stream.next();
				return null;
			}

			return {
				startState: function () {
					return {
						Tokenize: tokenMinilang,
						BraceLevel: 0,
						InsideString: false,
						CommentLevel: 0
					};
				},
				token: function (Stream, State) {
					return (State.Tokenize || tokenMinilang)(Stream, State);
				},
				lineComment: '--'
			};
		});

		CodeMirror.registerHelper("wordChars", "minilang", /[\w$]/);

		CodeMirror.defineMIME("text/x-minilang", "minilang");

		IPython.notebook.get_cells().map(
			function(c) { return c.code_mirror.options.indentWithTabs = true; }
		);
		CodeMirror.defaults.indentWithTabs = true;
	}

	return {onload};
});
