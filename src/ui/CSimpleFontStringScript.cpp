#include "ui/CSimpleFontStringScript.hpp"
#include "ui/CSimpleFont.hpp"
#include "ui/CSimpleFontString.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"
#include <cstdint>
#include <cctype>


// TEMPORARY SOLUTION (based on lstrlib.c from LUA)
/* maximum size of each formatted item (> len(format('%99.99f', -1e308))) */
#define MAX_ITEM 512
/* valid flags in a format specification */
#define FLAGS "-+ #0"
/*
** maximum size of each format specification (such as '%-099.99d')
** (+10 accounts for %99.99x plus margin of error)
*/
#define MAX_FORMAT (sizeof(FLAGS) + sizeof(LUA_INTFRMLEN) + 10)

#define uchar(c) ((unsigned char)(c))


static void addchar(char* b, char ch) {
    auto len = strlen(b);
    b[len++] = ch;
    b[len] = '\0';
}

static void addquoted(lua_State* L, char* b, int arg) {
    size_t l;
    const char* s = luaL_checklstring(L, arg, &l);
    addchar(b, '"');
    while (l--) {
        switch (*s) {
        case '"':
        case '\\':
        case '\n': {
            addchar(b, '\\');
            addchar(b, *s);
            break;
        }
        case '\r': {
            strcat(b, "\\r");
            break;
        }
        case '\0': {
            strcat(b, "\\000");
            break;
        }
        default: {
            addchar(b, *s);
            break;
        }
        }
        s++;
    }
    addchar(b, '"');
}

static const char* scanformat(lua_State* L, const char* strfrmt, char* form) {
    const char* p = strfrmt;
    while (*p != '\0' && strchr(FLAGS, *p) != NULL)
        p++; /* skip flags */
    if ((size_t)(p - strfrmt) >= sizeof(FLAGS))
        luaL_error(L, "invalid format (repeated flags)");
    if (isdigit(uchar(*p)))
        p++; /* skip width */
    if (isdigit(uchar(*p)))
        p++; /* (2 digits at most) */
    if (*p == '.') {
        p++;
        if (isdigit(uchar(*p)))
            p++; /* skip precision */
        if (isdigit(uchar(*p)))
            p++; /* (2 digits at most) */
    }
    if (isdigit(uchar(*p)))
        luaL_error(L, "invalid format (width or precision too long)");
    *(form++) = '%';
    strncpy(form, strfrmt, p - strfrmt + 1);
    form += p - strfrmt + 1;
    *form = '\0';
    return p;
}

static void addintlen(char* form) {
    size_t l = strlen(form);
    char spec = form[l - 1];
    strcpy(form + l - 1, LUA_INTFRMLEN);
    form[l + sizeof(LUA_INTFRMLEN) - 2] = spec;
    form[l + sizeof(LUA_INTFRMLEN) - 1] = '\0';
}

static int str_format(lua_State* L, char* b) {
    int arg = 2;
    size_t sfl;
    const char* strfrmt = luaL_checklstring(L, arg, &sfl);
    const char* strfrmt_end = strfrmt + sfl;
    while (strfrmt < strfrmt_end) {
        if (*strfrmt != '%')
            addchar(b, *strfrmt++);
        else if (*++strfrmt == '%')
            addchar(b, *strfrmt++); /* %% */
        else {                            /* format item */
            char form[MAX_FORMAT];        /* to store the format (`%...') */
            char buff[MAX_ITEM];          /* to store the formatted item */
            arg++;
            strfrmt = scanformat(L, strfrmt, form);
            switch (*strfrmt++) {
            case 'c': {
                sprintf(buff, form, (int)luaL_checknumber(L, arg));
                break;
            }
            case 'd':
            case 'i': {
                addintlen(form);
                sprintf(buff, form, (LUA_INTFRM_T)luaL_checknumber(L, arg));
                break;
            }
            case 'o':
            case 'u':
            case 'x':
            case 'X': {
                addintlen(form);
                sprintf(buff, form, (unsigned LUA_INTFRM_T)luaL_checknumber(L, arg));
                break;
            }
            case 'e':
            case 'E':
            case 'f':
            case 'g':
            case 'G': {
                sprintf(buff, form, (double)luaL_checknumber(L, arg));
                break;
            }
            case 'q': {
                addquoted(L, b, arg);
                continue; /* skip the 'addsize' at the end */
            }
            case 's': {
                size_t l;
                const char* s = luaL_checklstring(L, arg, &l);
                if (!strchr(form, '.') && l >= 100) {
                    /* no precision and string is too long to be formatted;
                       keep original string */
                    continue; /* skip the `addsize' at the end */
                } else {
                    sprintf(buff, form, s);
                    break;
                }
            }
            default: { /* also treat cases `pnLlh' */
                return luaL_error(L, "invalid option " LUA_QL("%%%c") " to " LUA_QL("format"), *(strfrmt - 1));
            }
            }
            strcat(b, buff);
        }
    }
    return 1;
}
// END OF TEMPORARY SOLUTION

int32_t CSimpleFontString_IsObjectType(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetObjectType(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetDrawLayer(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetDrawLayer(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetVertexColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetAlpha(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetAlpha(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetAlphaGradient(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_Show(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    string->Show();

    return 0;
}

int32_t CSimpleFontString_Hide(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    string->Hide();

    return 0;
}

int32_t CSimpleFontString_IsVisible(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_IsShown(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetFontObject(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetFontObject(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    CSimpleFont* font = nullptr;

    if (lua_type(L, 2) == LUA_TTABLE) {
        lua_rawgeti(L, 2, 0);
        font = static_cast<CSimpleFont*>(lua_touserdata(L, -1));
        lua_settop(L, -2);

        if (!font) {
            luaL_error(L, "%s:SetFontObject(): Couldn't find 'this' in font object", string->GetDisplayName());
        }

        if (!font->IsA(CSimpleFont::GetObjectType())) {
            luaL_error(L, "%s:SetFontObject(): Wrong object type, expected font", string->GetDisplayName());
        }
    } else if (lua_type(L, 2) == LUA_TSTRING) {
        auto fontName = lua_tolstring(L, 2, nullptr);
        font = CSimpleFont::GetFont(fontName, 0);

        if (!font) {
            luaL_error(L, "%s:SetFontObject(): Couldn't find font named %s", string->GetDisplayName(), fontName);
        }
    } else if (lua_type(L, 2) != LUA_TNIL) {
        luaL_error(L, "Usage: %s:SetFontObject(font or \"font\" or nil)", string->GetDisplayName());
    }

    string->SetFontObject(font);

    return 0;
}

int32_t CSimpleFontString_GetFont(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetFont(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetFieldSize(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetText(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    if (!string->m_font) {
        luaL_error(L, "%s:SetText(): Font not set", string->GetDisplayName());
    }

    const char* text = lua_tolstring(L, 2, 0);
    string->SetText(text, 1);

    return 0;
}

int32_t CSimpleFontString_SetFormattedText(lua_State* L) {
    if (lua_type(L, 1) != LUA_TTABLE) {
        luaL_error(L, "Attempt to find 'this' in non-table object (used '.' instead of ':' ?)");
        return 0;
    }

    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    if (!string->m_font) {
        luaL_error(L, "%s:SetText(): Font not set", string->GetDisplayName());
        return 0;
    }

    char b[2048] = {};
    str_format(L, b);
    string->SetText(b, 0);

    return 0;
}

int32_t CSimpleFontString_GetTextColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetTextColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetShadowColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetShadowColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetShadowOffset(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetShadowOffset(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetSpacing(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetSpacing(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetTextHeight(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetStringWidth(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetStringHeight(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetJustifyH(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetJustifyH(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetJustifyV(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetJustifyV(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_CanNonSpaceWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetNonSpaceWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_CanWordWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetWordWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetIndentedWordWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetIndentedWordWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

FrameScript_Method SimpleFontStringMethods[NUM_SIMPLE_FONT_STRING_SCRIPT_METHODS] = {
    { "IsObjectType",           &CSimpleFontString_IsObjectType },
    { "GetObjectType",          &CSimpleFontString_GetObjectType },
    { "GetDrawLayer",           &CSimpleFontString_GetDrawLayer },
    { "SetDrawLayer",           &CSimpleFontString_SetDrawLayer },
    { "SetVertexColor",         &CSimpleFontString_SetVertexColor },
    { "GetAlpha",               &CSimpleFontString_GetAlpha },
    { "SetAlpha",               &CSimpleFontString_SetAlpha },
    { "SetAlphaGradient",       &CSimpleFontString_SetAlphaGradient },
    { "Show",                   &CSimpleFontString_Show },
    { "Hide",                   &CSimpleFontString_Hide },
    { "IsVisible",              &CSimpleFontString_IsVisible },
    { "IsShown",                &CSimpleFontString_IsShown },
    { "GetFontObject",          &CSimpleFontString_GetFontObject },
    { "SetFontObject",          &CSimpleFontString_SetFontObject },
    { "GetFont",                &CSimpleFontString_GetFont },
    { "SetFont",                &CSimpleFontString_SetFont },
    { "GetText",                &CSimpleFontString_GetText },
    { "GetFieldSize",           &CSimpleFontString_GetFieldSize },
    { "SetText",                &CSimpleFontString_SetText },
    { "SetFormattedText",       &CSimpleFontString_SetFormattedText },
    { "GetTextColor",           &CSimpleFontString_GetTextColor },
    { "SetTextColor",           &CSimpleFontString_SetTextColor },
    { "GetShadowColor",         &CSimpleFontString_GetShadowColor },
    { "SetShadowColor",         &CSimpleFontString_SetShadowColor },
    { "GetShadowOffset",        &CSimpleFontString_GetShadowOffset },
    { "SetShadowOffset",        &CSimpleFontString_SetShadowOffset },
    { "GetSpacing",             &CSimpleFontString_GetSpacing },
    { "SetSpacing",             &CSimpleFontString_SetSpacing },
    { "SetTextHeight",          &CSimpleFontString_SetTextHeight },
    { "GetStringWidth",         &CSimpleFontString_GetStringWidth },
    { "GetStringHeight",        &CSimpleFontString_GetStringHeight },
    { "GetJustifyH",            &CSimpleFontString_GetJustifyH },
    { "SetJustifyH",            &CSimpleFontString_SetJustifyH },
    { "GetJustifyV",            &CSimpleFontString_GetJustifyV },
    { "SetJustifyV",            &CSimpleFontString_SetJustifyV },
    { "CanNonSpaceWrap",        &CSimpleFontString_CanNonSpaceWrap },
    { "SetNonSpaceWrap",        &CSimpleFontString_SetNonSpaceWrap },
    { "CanWordWrap",            &CSimpleFontString_CanWordWrap },
    { "SetWordWrap",            &CSimpleFontString_SetWordWrap },
    { "GetIndentedWordWrap",    &CSimpleFontString_GetIndentedWordWrap },
    { "SetIndentedWordWrap",    &CSimpleFontString_SetIndentedWordWrap }
};
