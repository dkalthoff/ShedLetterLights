#ifndef WebContent_h
#define WebContent_h

#include "LightsService.h"

class WebContent
{   
  public:
    const String defaultPage = "<!doctype html>"
                "<html lang=\"en\">"
                "<head>"
                    "<!-- Required meta tags -->"
                    "<meta charset=\"utf-8\">"
                    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                
                    "<!-- Bootstrap CSS -->"
                    "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3\" crossorigin=\"anonymous\">"
                    "<link rel=\"shortcut icon\" href=\"https://bit.ly/3IaoNdP\" type=\"image/x-icon\" />"
                    "<title>Shed Letter K Lights</title>"
                "</head>"
                "<body style=\"background-color: lightgray\">"
                  "<div class=\"container\"><a href=\"/\" class=\"nav-link\">Shed Letter K Lights</a></div>"
                  "<div id=\"menu\"></div>"
                  "<div id=\"cp\"></div>"                  
                  "<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p\" crossorigin=\"anonymous\"></script>"
                  "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js\"></script>"
                  "<script src=\"/scripts/defaultPage.js\"></script>"
                "</body>"
                "</html>";

    const String defaultPage_JS = "function g(cp,pc){"
                              "return $.get('/contentpage/'+cp).done(function(r){"
                                "$('#'+pc).html(r);"
                            "});}"
                            "function initMenu(){"
                              "$('.cp').click(function(){g($(this).html(),'cp');});"
                            "}"
                            "function initBtn(){"
                              "$('.btn').click(function(e){e.preventDefault();$.post($('form').attr('action'),$('form').serialize()).done(function(){alert('Updated');});});"
                            "}"
                    "$(document).ready(function(){"
                      "g('Scenes','cp').done(initBtn);"
                      "g('Menu','menu').done(initMenu);"
                    "});";

    const String contentPage_Menu = "<ul class=\"nav justify-content-center\">"
                                      "<li class=\"nav-item\"><a class=\"nav-link cp\" href=\"#\">Scenes</a></li>"
                                      "<li class=\"nav-item\"><a class=\"nav-link cp\" href=\"#\">Static</a></li>"
                                      "<li class=\"nav-item\"><a class=\"nav-link cp\" href=\"#\">Pulse</a></li>"
                                      "<li class=\"nav-item\"><a class=\"nav-link cp\" href=\"#\">Segments</a></li>"
                                      "<li class=\"nav-item\"><a class=\"nav-link cp\" href=\"#\">Random</a></li>"
                                    "</ul>";
                              
    const String contentPage_Scenes = "<div class=\"container mb-2\">"
                                        "<h4>Scenes</h4>"
                                        "<form action=\"/api/scenes\" method=\"post\" class=\"row needs-validation\">"
                                            "<div class=\"col-9\">"
                                                "<select name=\"scenesType\" id=\"scenesType\" class=\"form-select form-select-md mb-3\" aria-label=\"Scene Types\" required>"
                                                    "<option value=\"\"></option>"
                                                    "<option value=\"0\">Avon Lakers</option>"
                                                    "<option value=\"1\">Christmas</option>"
                                                    "<option value=\"2\">Easter</option>"
                                                    "<option value=\"3\">Forest</option>"
                                                    "<option value=\"4\">Heat</option>"
                                                    "<option value=\"5\">Lava</option>"
                                                    "<option value=\"6\">Ocean</option>"
                                                    "<option value=\"7\">Party</option>"
                                                    "<option value=\"8\">Patriotic</option>"
                                                    "<option value=\"9\">Purple Pride</option>"
                                                    "<option value=\"10\">Rainbow</option>"
                                                    "<option value=\"11\">Random</option>"
                                                    "<option value=\"12\">Valentines</option>"
                                                "</select>"
                                            "</div>"
                                            "<div class=\"col-3\">"
                                                "<button type=\"submit\" class=\"btn btn-primary\">Submit</button>"
                                            "</div>"
                                        "</form>"
                                      "</div>";
                    
   const String contentPage_Static = "<div class=\"container mb-4\">"
                                      "<h4>Static Color</h4>"
                                      "<form action=\"/api/selectedStatic\" method=\"get\" class=\"row\">"
                                          "<div class=\"col-2\">"
                                              "<input type=\"color\" class=\"form-control form-control-color\" id=\"selectedStaticColor\" name=\"selectedStaticColor\" value=\"#563d7c\" title=\"Choose your color\" />"
                                          "</div>"
                                          "<div class=\"col-10\">"
                                              "<button type=\"submit\" class=\"btn btn-primary\">Submit</button>"
                                          "</div>"
                                      "</form>"
                                    "</div>";

    const String contentPage_Pulse = "<div class=\"container mb-4\">"
                                      "<h4>Pulse Color</h4>"
                                      "<form action=\"/api/pulse\" method=\"get\" class=\"row\">"
                                          "<div class=\"col-2\">"
                                              "<input type=\"color\" class=\"form-control form-control-color\" id=\"selectedStaticColorInput\" value=\"#563d7c\" title=\"Choose your color\" />"
                                          "</div>"
                                          "<div class=\"col-10\">"
                                              "<button type=\"submit\" class=\"btn btn-primary\">Submit</button>"
                                          "</div>"
                                        "</form>"
                                    "</div>";

    const String contentPage_Segments = "<div class=\"container mb-4\">"
                                          "<h4>Segments Color</h4>"
                                          "<form action=\"/api/segments\" method=\"get\" class=\"row\">"
                                              "<div class=\"col-2\"><input type=\"color\" class=\"form-control form-control-color\" id=\"selectedStaticColor1Input\" value=\"#563d7c\" title=\"Choose your color\" /></div>"
                                              "<div class=\"col-2\"><input type=\"color\" class=\"form-control form-control-color\" id=\"selectedStaticColor2Input\" value=\"#563d7c\" title=\"Choose your color\" /></div>"
                                              "<div class=\"col-2\"><input type=\"color\" class=\"form-control form-control-color\" id=\"selectedStaticColor3Input\" value=\"#563d7c\" title=\"Choose your color\" /></div>"
                                              "<div class=\"col-6\">"
                                                  "<button type=\"submit\" class=\"btn btn-primary\">Submit</button>"
                                              "</div>"
                                          "</form>"
                                        "</div>";

    const String contentPage_Random = "<div class=\"container mb-3\">"
                                        "<h4>Random</h4>"
                                        "<ul class=\"nav justify-content-left\">"
                                            "<li class=\"nav-item\"><a href=\"/api/randomStatic\" class=\"nav-link\">Color</a></li>"
                                            "<li class=\"nav-item\"><a href=\"/api/randomPulse\" class=\"nav-link\">Pulse Color</a></li>"
                                            "<li class=\"nav-item\"><a href=\"/api/randomStaticSegments\" class=\"nav-link\">Segment Colors</a></li>"
                                        "</ul>"
                                    "</div>";
};

WebContent webContent;
#endif
