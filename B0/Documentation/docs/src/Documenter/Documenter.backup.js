
/** Coded by Mathew Kurian **/

(function (window) {

    if (!Array.prototype.forEach) {
        Array.prototype.forEach = function (b) {
            if (typeof b != "function") {
                throw new TypeError()
            }
            var a = this.length,
                d = arguments[1],
                c;
            for (c = 0; c < a; c++) {
                if (c in this) {
                    b.call(d, this[c], c, this)
                }
            }
        }
    };

    /* Coded by Mathew Kurian */

    Array.prototype.nextIndexOfNotChar = function (i, char) {
        while (this[i] == char) {
            i++;
        }

        return i;
    };

    /* Coded by Mathew Kurian */

    String.prototype.nextIndexOfNotChar = function (i, char) {

        var array = this.split('');

        while (array[i] == char) {
            i++;
        }

        return i;
    };

    /* Coded by Mathew Kurian */

    String.prototype.powerTrim = function () {
        var inDoubleQuotes = false,
            temp,
            s = this.split('');

        for (var i = 0; i < s.length; i++) {
            if (s[i] == "\"" && !inDoubleQuotes)
                inDoubleQuotes = true;
            else if (s[i] == "\"" && inDoubleQuotes)
                inDoubleQuotes = false;
            else if (s[i] == ' ' && !inDoubleQuotes)
                s.splice(i, (temp = s.nextIndexOfNotChar(i, ' ')) - i - 1);

        }

        return s.join('');

    };

    /* Coded by Mathew Kurian */

    Array.prototype.isNextNonWhiteSpaceChar = function (i, char) {
        if (this[i] == char)
            return true;

        while (this[i] == ' ' || this[i] == '\t' || this[i] == '\n')
            if (this[++i] == char)
                return true;

        return false;
    };

    Array.prototype.isNextNonWhiteSpaceDoubleChar = function (i, char1, char2 ) {
        if (this[i] == char1 && this[i + 1] == char2)
            return true;

        while (this[i] == ' ' || this[i] == '\t' || this[i] == '\n')
            if (this[++i] == char1)
                if (this[i + 1] == char2)
                    return true;            

        return false;
    };

    var Documenter = {};

    Documenter.classIndex = 0;
    Documenter.sidebarEnabled = true;

    Documenter.Legend = [{
        title: "pure-virtual",
        iconType: "methodPureVirtual"
    }, {
        title: "virtual",
        iconType: "methodVirtual"
    }, {
        title: "virtual-final",
        iconType: "methodVirtualFinal"
    }, {
        title: "accessor",
        iconType: "methodAccessor"
    }, {
        title: "mutator",
        iconType: "methodMutator"
    }, {
        title: "factory",
        iconType: "methodFactory"
    }, {
        title: "builder",
        iconType: "methodBuilder"
    }, {
        title: "static",
        iconType: "methodStatic"
    }, {
        title: "overridden",
        iconType: "methodOverridden"
    }, {
        title: "constructor",
        iconType: "methodConstructor"
    }, {
        title: "deconstructor",
        iconType: "methodDeconstructor"
    }, ];

    Documenter.GenerateLegend = function () {
         var divLegend = $('<div class = "legend animator"></div>');

        Documenter.Legend.forEach(function (group) {
                divLegend.append($('<div class = "group animator"><div class = "icon iconType-' + group.iconType + '"></div><div class = "title animator">' + group.title + '</div></div>'));
        });

        divLegend.prepend('<div class = "controller">INCLUDE</div>');
        divLegend.prepend('<div class = "controller">SOURCE</div>');
        divLegend.prepend('<div class = "controller controller-selected">DOCS</div>');

        return divLegend;
    }

    Documenter.Initialize = function (data, divDoc, divSidebarBtn, selectedClassBtn) {
        /** INITIALIZE **/

        var divSidebar = $('<div class = "sidebar animator"></div>');
        var divContent = $('<div class = "content animator"></div>');

        var divWide = $('<div class = "wide-container animator"></div>');
        var divSingle = $('<div class = "single-container"></div>');
        var divIntro = $('<div class = "introduction"></div>');
        var divIntroFloating = $('<div class = "floating-panel"></div>');

        /** PREPARE **/

        var funcSiderbarToggle = function () {
            Documenter.Translate3dX(divSidebar, Documenter.sidebarEnabled ? "-330px" : "0");
            Documenter.Translate3dX(divContent, Documenter.sidebarEnabled ? "-330px" : "0");

            Documenter.sidebarEnabled ? $(divSidebarBtn).removeClass(selectedClassBtn) : $(divSidebarBtn).addClass(selectedClassBtn);

            Documenter.sidebarEnabled = !Documenter.sidebarEnabled;
        };

        funcSiderbarToggle();

        $(divSidebarBtn).on("click", funcSiderbarToggle);

        divSingle.css('background', 'url(' + data.background + ') center center no-repeat');
        divSingle.css('background-size', 'cover');

        /** APPEND **/

        divIntroFloating.append('<div class = "title">' + data.title + '</div><div class = "catchPhrase">' + data.catchPhrase + '</div><div class = "description">' + data.description + '</div>');
        divIntro.append(divIntroFloating);
        divSingle.append(divIntro);
        divWide.append(divSingle);

        divContent.append(divWide);
        divSidebar.append('<div class = "sidebar-item", onclick = "Documenter.SlideContainer(' + (Documenter.classIndex++) + ')">' + "HOME" + '</div>');

        data.classes.forEach(function (Class) {

            /** INITIALIZE **/

            var divSingle = $('<div class = "single-container"></div>');
            var divLegend = Documenter.GenerateLegend();
            var divSectionLeft = $('<div class = "left"></div>');
            var divSectionRight = $('<div class = "right"></div>');
            var divSectionRightTall = $('<div class = "tall-3-container animator"></div>')
            var divSectionRightPaddedHeader = $('<div class = "paddedOverflow"></div>');
            var divSectionRightPaddedCpp = $('<div class = "paddedOverflow"></div>');
            var divSectionRightPaddedBlocks = $('<div class = "paddedOverflow"></div>');
            var div = $('<div></div>');

            /** PREPARE **/

            divSingle.css('background', 'url(' + Class.background + ') center center no-repeat');
            divSingle.css('background-size', 'cover');

            /** APPEND **/

            div.append('<div class = "title">' + Class["title"] + '</div>');
            div.append('<div class = "description">' + Class["description"] + '</div>');
            div.append('<div class = "extends-label">' + "EXTENDS" + '</div>');
            div.append('<div class = "extends">' + Class["extends"].join().replace(/,/g, '<br/>') + '</div>');

            divSectionLeft.append(div);
            divSidebar.append('<div class = "sidebar-item",  onclick = "Documenter.SlideContainer(' + (Documenter.classIndex++) + ')">' + Class["title"] + '<div>' + Class["dataType"] + '</div></div>');

            divSectionRightTall.append(divSectionRightPaddedBlocks);
            divSectionRightTall.append(divSectionRightPaddedCpp);
            divSectionRightTall.append(divSectionRightPaddedHeader);
            divSectionRight.append(divSectionRightTall);
            divSingle.append(divSectionLeft);
            divSingle.append(divSectionRight);
            divSingle.append(divLegend);

            divWide.append(divSingle);

            var rawCode = function (Class, type, appendTo, ext) {
                var divBlock = $('<div class = "block"></div>');
                var divHeader = $('<div class = "header headerType-normal">' + Class.title + ext + '</div>');
                var divCodeSection = $('<div class = "section sectionType-code"></div>');

                if (typeof Class[type] !== 'undefined')
                    divCodeSection.append('<div class = "data", data = "' + Class[type].replace(/\"/g, 'Qx1').replace(/class/g, "Zx1") + '">' + Class.rawHeader + '</div>');
                else
                    divCodeSection.append('<div class = "data", data = "File not found!">File not found!</div>');


                divBlock.append(divHeader);
                divBlock.append(divCodeSection);
                appendTo.append(divBlock);
            }

            rawCode(Class, "rawCpp", divSectionRightPaddedCpp, ".cpp");
            rawCode(Class, "rawHeader", divSectionRightPaddedHeader, ".h");


            Class.blocks.forEach(function (Block) {

                /** INITIALIZE **/

                var div = $('<div class = "block"></div>');
                var divCollapsible = $('<div class = "collapsible"></div>');

                var divIcons = '';

                Block.header.icons.forEach(function(icon){
                    divIcons += '<div class = "icon iconType-' + icon + '"></div>';
                });

                var divHeader = $('<div class = "header headerType-' + Block.header.type + '">' + divIcons + Block.header.title + '</div>');

                /** PREPARE **/

                $(divHeader).on('click', function () {
                    var headerHasClass = $(this).hasClass('header-borderless');
                    var collapsible = $(this).next();
                    headerHasClass ? $(this).removeClass('header-borderless') : $(this).addClass('header-borderless');
                    collapsible.css('height', headerHasClass ? 'auto' : '0px');
                })

                /** APPEND **/

                div.append(divHeader);
                div.append(divCollapsible);
                divSectionRightPaddedBlocks.append(div);

                Block.sections.forEach(function (Section) {
                    var _div = $('<div class = "section sectionType-' + Section.type + '"></div>');

                    if (typeof Section.args !== "undefined")
                        Section.args.forEach(function (arg) {
                            
                            /** INITIALIZE **/

                            var __div = $('<div />', {
                                class: 'arg'
                            });

                            /** APPEND **/

                            __div.append('<div class = "title">' + arg.title + '</div>')
                            __div.append('<div class = "description">' + arg.description + '</div>')

                            _div.append(__div);

                        });

                    if (typeof Section.data !== "undefined")
                        _div.append('<div class = "data", data = "' + Section.data.replace(/\"/g, 'Qx1') + '">' + 
                            (Section.type != "code" ? Section.data.replace(/`(.*?)`/g, '<span class = "inline-code">$1</span>') : Section.data) + '</div>');


                    divCollapsible.append(_div);

                });

            });

        });

        /** APPEND **/

        $(divDoc).append(divSidebar);
        $(divDoc).append(divContent);

        /** NEXT STEPS **/

        Documenter.SlidingContainerPrep(".wide-container");
        Documenter.FormatCode();
        Documenter.AddControllerBehavior();

    }

    var slidingPanel = function (container, index) {
        var length = $(container).children().length;
        var moveTo = index / length * 100;

        if (moveTo > 100) return;

        Documenter.Translate3dX(container, moveTo + "%");
    }

    var slidingPanelPrep = function (container) {
        var length = $(container).children().length;

        $(container).css("width", (length * 100) + "%");
        $(container).children().css("width", (100 / length) + "%");
    }


    Documenter.Translate3dX = function (container, percent) {
        $(container).css({
            'transform': 'translate3d(' + percent + ',0,0)',
            '-webkit-transform': 'translate3d(' + percent + ',0,0)',
            '-moz-transform': 'translate3d(' + percent + ',0,0)',
            '-ms-transform': 'translate3d(' + percent + ',0,0)',
        });
    }

    Documenter.Translate3dY = function (container, percent) {
        $(container).css({
            'transform': 'translate3d(0, ' + percent + ',0)',
            '-webkit-transform': 'translate3d(0, ' + percent + ',0)',
            '-moz-transform': 'translate3d(0, ' + percent + ',0)',
            '-ms-transform': 'translate3d(0, ' + percent + ',0)',
        });
    }    

    Documenter.SlideContainer = function (index) {
        slidingPanel(".wide-container", -index);
    }

    Documenter.SlidingContainerPrep = function () {
        slidingPanelPrep(".wide-container");
    }

    Documenter.AddControllerBehavior = function () {
        $('.controller').on('click', function () {
            var type = $(this).text();

            var distance = 0;

            switch (type) {
            case "INCLUDE":
                distance = "-66.666666666666666666%";
                break;
            case "SOURCE":
                distance = "-33.33333333333333333%";
                break;
            case "DOCS":
                distance = "0%";
                break;
            }

            $(this).siblings().removeClass('controller-selected');
            $(this).removeClass('controller-selected');
            $(this).addClass('controller-selected');

            Documenter.Translate3dY($(this).parent().siblings('.right').children('.tall-3-container'), distance);
        });
    }

    Documenter.FormatCode = function () {
        $(".sectionType-code").each(function (i) {
                if(i != 0) return;

            var divData = $(this).children()
                .eq(0);

            var text = divData.attr('data');

            if (typeof text === 'undefined')
                text = "Source is empty!";

            text = text.powerTrim()
                       .trim()
                       .split('');

            var             tabCount = 0,
                inDoubleQuotes = inSingleQuotes = inInlineComment = inMultilineComment = false,
                 formatted = '<div class = "codeLine"></div><div class = "codeLine"><div class = "codeChars" style = "width: ' + (100 - (2 * tabCount + 5)) + '%;">';

            var tabMaker = function (count) {
                return '<div class = "codeChars" style = "width: ' + (2 * count) + '%;"></div>';
            };

            for (var i = 0; i < text.length; i++) {
                if (text[i] == '{') {

                    formatted += 
                        '</div></div><div class = "codeLine">' +
                        tabMaker(tabCount) + 
                        text[i] +
                        '</div><div class = "codeLine">' +
                        tabMaker(++tabCount) +
                        '<div class = "codeChars" style = "width: ' + (100 - (2 * tabCount + 5)) + '%;">';

                    if (text[i + 1] == ' ') i++;

                } else if (text[i] == '<') {
                    formatted += "&lt;";
                } else if (text[i] == '>') {
                    formatted += "&gt;";
                } else if (text[i] == '}') {

                    formatted +=    '</div></div><div class = "codeLine">' + 
                                    tabMaker(--tabCount) + 
                                    text[i] + 
                                    (text[i + 1] == ';' ? text[i + 1] : '') + 
                                    '</div>' +
                                    (!text.isNextNonWhiteSpaceChar(i + 1, '}') ? 
                                        '<div class = "codeLine">' + tabMaker(tabCount) + '<div class = "codeChars" style = "width: ' + (100 - (2 * tabCount + 5)) + '%;">'
                                        : '');

                    

                    if (text[i + 1] == ' '&& !inMultilineComment) i++;
                    if (text[i + 1] == ';') i++;

                } else if (text[i] == ';') {
                    var foundComment = text.isNextNonWhiteSpaceChar(i + 1, '\/');
                    formatted +=    text[i] + 
                                    (inInlineComment ? '</span>' : (foundComment ? '<span class = "comment">' : '')) + 
                                    (!foundComment ? '</div></div>' : '')+
                                    (!(text.isNextNonWhiteSpaceChar(i + 1, '}') || foundComment) ? 
                                        '<div class = "codeLine">' + 
                                        tabMaker(tabCount) + 
                                        '<div class = "codeChars" style = "width: ' +  (100 - (2 * tabCount + 5)) + '%;">' 
                                        : '' );

                    if (inInlineComment) inInlineComment = false;
                    if (foundComment) inInlineComment = true;
                    if (text[i + 1] == ' ' && !inInlineComment && !inMultilineComment) i++;

                } else if (text[i] == 'Q' && text[i + 1] == 'x' && text[i + 2] == '1' && !inDoubleQuotes) {

                    inDoubleQuotes = true;
                    formatted +=    '<span class = "string">' + 
                                    text[i] + 
                                    text[i + 1] + 
                                    text[i + 2];
                    i += 2;

                } else if (text[i] == 'Q' && text[i + 1] == 'x' && text[i + 2] == '1' && inDoubleQuotes) {

                    inDoubleQuotes = false;
                    formatted +=    text[i] + 
                                    text[i + 1] + 
                                    text[i + 2] + 
                                    '</span>';
                    i += 2;

                } else if (text[i] == "'" && !inDoubleQuotes && !inSingleQuotes) {

                    inSingleQuotes = true;
                    formatted +=    '<span class = "character">' + 
                                    text[i];

                } else if (text[i] == "'" && !inDoubleQuotes && inSingleQuotes) {

                    inSingleQuotes = false;
                    formatted += text[i] + '</span>';

                } else if (text[i] == '$') {
                    var foundMultilineComment = text.isNextNonWhiteSpaceDoubleChar(i + 1, '/', '*');

                    formatted +=    (inInlineComment ? '</span>' : '') + 
                                    '</div></div>' + 
                                    (foundMultilineComment && !inMultilineComment
                                        ? '<div class = "commentBlock">' : '') +
                                    '<div class = "codeLine">'+ tabMaker(tabCount) + '<div class = "codeChars" style = "width: ' + (100 - (2 * tabCount + 5)) + '%;">'
                                    + (inMultilineComment ? '&nbsp;' : '');

                    if (!inMultilineComment && foundMultilineComment) inMultilineComment++;
                    if (inInlineComment) inInlineComment = false;
                    if (text[i + 1] == ' ' && !inMultilineComment) i++;

                } else if (text[i] == '/' && text[i + 1] == '/' && !inInlineComment  && !inMultilineComment) {

                    inInlineComment = true;

                    formatted +=    '<span class = "comment">' + 
                                    text[i] + 
                                    text[i + 1];

                    i++;

                } else if (text[i] == '/' && text[i + 1] == '*' ) {

                    inMultilineComment++;

                    formatted +=  (inMultilineComment == 1 ? '<div class = "commentBlock">' : '') +
                                    text[i] + 
                                    text[i + 1];

                    i++;

                } else if (text[i] == '*' && text[i + 1] == '/' && inMultilineComment) {

                    inMultilineComment--;

                    formatted +=  
                                    text[i] + 
                                    text[i + 1] + !inMultilineComment ? '</div>' : '';

                    i++;

                } else
                    formatted += text[i];

            }

            formatted += '</div><div class = "codeLine"></div>';

            formatted = formatted.replace(/(void|public|private|using|LPCWSTR|int|float|HINSTANCE|LRESULT|HRESULT|bool|protected)/g, '<span class = "reserved-1">$1</span>')
                                 .replace(/(namespace|typedef|final)/g, '<span class = "reserved-3">$1</span>')
                                 .replace(/(goto|cout|struct|Zx1|while|for|return|if|else|else if)/g, '<span class = "reserved-2">$1</span>')
                                 .replace(/(#include|#define|#ifndef|#endif|virtual)/g, '<span class = "reserved-preprocessor">$1</span>')
                                 .replace(/Qx1/g, '\"')
                                 .replace(/Zx1/g, "class")
                                 .trim();

            divData.html(formatted);

            divData.find('.codeLine').each(function (i) {
                $(this).prepend('<div class = "gutter">' + (i + 1) + '</div>')
            });

        });
    }

    window['Documenter'] = Documenter;

})(window);