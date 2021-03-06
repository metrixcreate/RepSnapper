<?xml version="1.0" encoding="utf-8"?>
<!-- Copyright 2003 Douglas Gregor -->
<!-- Distributed under the Boost Software License, Version 1.0. -->
<!-- (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt) -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:fo="http://www.w3.org/1999/XSL/Format"
                version="1.0">

  <!-- Import the FO stylesheet -->
  <xsl:import 
    href="http://docbook.sourceforge.net/release/xsl/current/fo/docbook.xsl"/>

  <xsl:param name="chapter.autolabel" select="0"/>
  <xsl:param name="refentry.generate.name" select="0"/>
  <xsl:param name="refentry.generate.title" select="1"/>
  <xsl:param name="fop1.extensions" select="1"/>
  <xsl:param name="make.year.ranges" select="1"/>
  <xsl:param name="ulink.show" select="0"/>

  <!-- The question and answer templates are copied here from the
       1.61.3 DocBook XSL stylesheets so that we can eliminate the emission
       of id attributes in the emitted fo:list-item-label elements. FOP
       0.20.5 has problems with these id attributes, and they are otherwise
       unused. -->
<xsl:template match="question">
  <xsl:variable name="id"><xsl:call-template name="object.id"/></xsl:variable>

  <xsl:variable name="entry.id">
    <xsl:call-template name="object.id">
      <xsl:with-param name="object" select="parent::*"/>
    </xsl:call-template>
  </xsl:variable>

  <xsl:variable name="deflabel">
    <xsl:choose>
      <xsl:when test="ancestor-or-self::*[@defaultlabel]">
        <xsl:value-of select="(ancestor-or-self::*[@defaultlabel])[last()]
                              /@defaultlabel"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$qanda.defaultlabel"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:variable>

  <fo:list-item id="{$entry.id}" xsl:use-attribute-sets="list.item.spacing">
    <fo:list-item-label end-indent="label-end()">
      <xsl:choose>
        <xsl:when test="$deflabel = 'none'">
          <fo:block/>
        </xsl:when>
        <xsl:otherwise>
          <fo:block>
            <xsl:apply-templates select="." mode="label.markup"/>
            <xsl:text>.</xsl:text> <!-- FIXME: Hack!!! This should be in the locale! -->
          </fo:block>
        </xsl:otherwise>
      </xsl:choose>
    </fo:list-item-label>
    <fo:list-item-body start-indent="body-start()">
      <xsl:choose>
        <xsl:when test="$deflabel = 'none'">
          <fo:block font-weight="bold">
            <xsl:apply-templates select="*[local-name(.)!='label']"/>
          </fo:block>
        </xsl:when>
        <xsl:otherwise>
          <xsl:apply-templates select="*[local-name(.)!='label']"/>
        </xsl:otherwise>
      </xsl:choose>
    </fo:list-item-body>
  </fo:list-item>
</xsl:template>

<xsl:template match="answer">
  <xsl:variable name="id"><xsl:call-template name="object.id"/></xsl:variable>
  <xsl:variable name="entry.id">
    <xsl:call-template name="object.id">
      <xsl:with-param name="object" select="parent::*"/>
    </xsl:call-template>
  </xsl:variable>

  <xsl:variable name="deflabel">
    <xsl:choose>
      <xsl:when test="ancestor-or-self::*[@defaultlabel]">
        <xsl:value-of select="(ancestor-or-self::*[@defaultlabel])[last()]
                              /@defaultlabel"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$qanda.defaultlabel"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:variable>

  <fo:list-item xsl:use-attribute-sets="list.item.spacing">
    <fo:list-item-label end-indent="label-end()">
      <xsl:choose>
        <xsl:when test="$deflabel = 'none'">
          <fo:block/>
        </xsl:when>
        <xsl:otherwise>
          <fo:block>
            <!-- FIXME: Hack!!! This should be in the locale! -->
            <xsl:variable name="answer.label">
              <xsl:apply-templates select="." mode="label.markup"/>
            </xsl:variable>
            <xsl:copy-of select="$answer.label"/>
            <xsl:if test="string($answer.label) != ''">
              <xsl:text>.</xsl:text>
            </xsl:if>
          </fo:block>
        </xsl:otherwise>
      </xsl:choose>
    </fo:list-item-label>
    <fo:list-item-body start-indent="body-start()">
      <xsl:apply-templates select="*[local-name(.)!='label']"/>
    </fo:list-item-body>
  </fo:list-item>
</xsl:template>

<!-- 

 The following rules apply syntax highlighting to phrases
 that have been appropriately marked up, the highlighting
 used is the same as that used by our CSS style sheets,
 but potentially we have the option to do better here
 since we can add bold and italic formatting quite easily
 
 -->

<xsl:template match="//programlisting/phrase[@role='keyword']">
  <fo:inline color="#0000AA"><xsl:apply-templates/></fo:inline>
</xsl:template>
<xsl:template match="//programlisting/phrase[@role='special']">
  <fo:inline color="#707070"><xsl:apply-templates/></fo:inline>
</xsl:template>
<xsl:template match="//programlisting/phrase[@role='preprocessor']">
  <fo:inline color="#402080"><xsl:apply-templates/></fo:inline>
</xsl:template>
<xsl:template match="//programlisting/phrase[@role='char']">
  <fo:inline color="teal"><xsl:apply-templates/></fo:inline>
</xsl:template>
<xsl:template match="//programlisting/phrase[@role='comment']">
  <fo:inline color="#800000"><xsl:apply-templates/></fo:inline>
</xsl:template>
<xsl:template match="//programlisting/phrase[@role='string']">
  <fo:inline color="teal"><xsl:apply-templates/></fo:inline>
</xsl:template>
<xsl:template match="//programlisting/phrase[@role='number']">
  <fo:inline color="teal"><xsl:apply-templates/></fo:inline>
</xsl:template>
<xsl:template match="//programlisting/phrase[@role='white_bkd']">
  <fo:inline color="#FFFFFF"><xsl:apply-templates/></fo:inline>
</xsl:template>
<xsl:template match="//programlisting/phrase[@role='dk_grey_bkd']">
  <fo:inline color="#999999"><xsl:apply-templates/></fo:inline>
</xsl:template>

<!--
Make all hyperlinks blue colored:
-->
<xsl:attribute-set name="xref.properties">
  <xsl:attribute name="color">blue</xsl:attribute>
</xsl:attribute-set>

<!--
Put a box around admonishments and keep them together:
-->
<xsl:attribute-set name="graphical.admonition.properties">
  <xsl:attribute name="border-color">#FF8080</xsl:attribute>
  <xsl:attribute name="border-width">1px</xsl:attribute>
  <xsl:attribute name="border-style">solid</xsl:attribute>
  <xsl:attribute name="padding-left">0.2cm</xsl:attribute>
  <xsl:attribute name="padding-right">0.2cm</xsl:attribute>
  <xsl:attribute name="padding-top">0.2cm</xsl:attribute>
  <xsl:attribute name="padding-bottom">0.2cm</xsl:attribute>
  <xsl:attribute name="keep-together.within-page">1</xsl:attribute>
  <xsl:attribute name="margin-left">0pt</xsl:attribute>
  <xsl:attribute name="margin-right">0pt</xsl:attribute>
</xsl:attribute-set>

<!--
Put a box around code blocks, also set the font size
and keep the block together if we can using the widows 
and orphans controls.  Hyphenation and line wrapping
is also turned on, so that long lines of code don't
bleed off the edge of the page, a carriage return
symbol is used as the hyphenation character:
-->
<xsl:attribute-set name="monospace.verbatim.properties">
  <xsl:attribute name="border-color">#DCDCDC</xsl:attribute>
  <xsl:attribute name="border-width">1px</xsl:attribute>
  <xsl:attribute name="border-style">solid</xsl:attribute>
  <xsl:attribute name="padding-left">0.2cm</xsl:attribute>
  <xsl:attribute name="padding-right">0.2cm</xsl:attribute>
  <xsl:attribute name="padding-top">0.2cm</xsl:attribute>
  <xsl:attribute name="padding-bottom">0.2cm</xsl:attribute>
  <xsl:attribute name="widows">6</xsl:attribute>
  <xsl:attribute name="orphans">40</xsl:attribute>
  <xsl:attribute name="font-size">9pt</xsl:attribute>
  <xsl:attribute name="hyphenate">true</xsl:attribute>
  <xsl:attribute name="wrap-option">wrap</xsl:attribute>
  <xsl:attribute name="hyphenation-character">&#x21B5;</xsl:attribute>
  <xsl:attribute name="margin-left">0pt</xsl:attribute>
  <xsl:attribute name="margin-right">0pt</xsl:attribute>
</xsl:attribute-set>

<xsl:param name="hyphenate.verbatim" select="1"></xsl:param>
<xsl:param name="monospace.font.family">monospace,Symbol</xsl:param>

  <!--Regular monospace text should have the same font size as code blocks etc-->
<xsl:attribute-set name="monospace.properties">
  <xsl:attribute name="font-size">9pt</xsl:attribute>
</xsl:attribute-set>
  
<!-- 
Put some small amount of padding around table cells, and keep tables
together on one page if possible:
-->
<xsl:attribute-set name="table.cell.padding">
  <xsl:attribute name="padding-left">0.2cm</xsl:attribute>
  <xsl:attribute name="padding-right">0.2cm</xsl:attribute>
  <xsl:attribute name="padding-top">0.2cm</xsl:attribute>
  <xsl:attribute name="padding-bottom">0.2cm</xsl:attribute>
</xsl:attribute-set>

  <!--Formal and informal tables have the same properties
      Using widow-and-orphan control here gives much better
      results for very large tables than a simple "keep-together"
      instruction-->
<xsl:attribute-set name="table.properties">
  <xsl:attribute name="keep-together.within-page">1</xsl:attribute>
</xsl:attribute-set>
<xsl:attribute-set name="informaltable.properties">
  <xsl:attribute name="keep-together.within-page">1</xsl:attribute>
</xsl:attribute-set>

<!--
General default options go here:
* Borders are mid-grey.
* Body text is not indented compared to the titles.
* Page margins are a rather small 0.5in, but we need
  all the space we can get for code blocks.
* Paper size is A4: an ISO standard, and just slightly smaller than US Letter.
* Use SVG graphics for admonishments: the bitmaps look awful in PDF's.
* Disable draft mode so we're not constantly trying to download the necessary graphic.
* Set default image paths to pull down direct from SVN: individual Jamfiles can override this
  and pass an absolute path to local versions of the images, but we can't get that here, so
  we'll use SVN instead so that most things "just work".
-->
<xsl:param name="table.frame.border.color">#DCDCDC</xsl:param>
<xsl:param name="table.cell.border.color">#DCDCDC</xsl:param>
<xsl:param name="body.start.indent">0pt</xsl:param>
<xsl:param name="page.margin.inner">0.5in</xsl:param>
<xsl:param name="page.margin.outer">0.5in</xsl:param>
<xsl:param name="paper.type">A4</xsl:param>
<xsl:param name="admon.graphics">1</xsl:param>
<xsl:param name="admon.graphics.extension">.svg</xsl:param>
<xsl:param name="draft.mode">no</xsl:param>
<xsl:param name="admon.graphics.path">http://svn.boost.org/svn/boost/trunk/doc/src/images/</xsl:param>
<xsl:param name="callout.graphics.path">http://svn.boost.org/svn/boost/trunk/doc/src/images/callouts/</xsl:param>
<xsl:param name="img.src.path">http://svn.boost.org/svn/boost/trunk/doc/html/</xsl:param>

<!-- Ideally we would use this to force top level sections
     to start on a new page, unfortunately this causes rather
     unfortunate page breaks in some Doxygen-generated
     documentation which uses <refentry> and <synopsis>
     sections :-(

<xsl:attribute-set name="section.level1.properties">
  <xsl:attribute name="break-before">page</xsl:attribute>
</xsl:attribute-set>

-->
  
</xsl:stylesheet>

