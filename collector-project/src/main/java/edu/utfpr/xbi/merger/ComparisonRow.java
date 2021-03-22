package edu.utfpr.xbi.merger;

public class ComparisonRow {
    private BrowserRow base;
    private BrowserRow target;
    private double imageDiff;
    private double chiSquared;
    private double phash;

    public ComparisonRow(BrowserRow base, BrowserRow target) {
        this.base = base;
        this.target = target;
    }

    public void setImageDiff(double imageDiff){ this.imageDiff = imageDiff; }
    public void setChiSquared(double chiSquared){
        this.chiSquared = chiSquared;
    }
    public void setPHash(double phash){ this.phash = phash; }

    private String getURL() {
        if (this.base != null)
            return this.base.getURL();
        return this.target.getURL();
    }

    private int getId() {
        if (this.base != null)
            return this.base.getId();
        return this.target.getId();
    }

    private String getTagName() {
        if (this.base != null)
            return this.base.getTagName();
        return this.target.getTagName();
    }

    private int getChildsNumber() {
        if (this.base != null)
            return this.base.getChildsNumber();
        return this.target.getChildsNumber();
    }

    private int getTextLength() {
        if (this.base != null)
            return this.base.getTextLength();
        return this.target.getTextLength();
    }

    private String getBasePlatform() {
        if (this.base != null)
            return this.base.getBrowserName();
        return null;
    }

    private String getTargetPlatform() {
        if (this.target != null)
            return this.target.getBrowserName();
        return null;
    }

    private float getBaseDPI() {
        if (this.base != null)
            return this.base.getDPI();
        return -1f;
    }

    private float getTargetDPI() {
        if (this.target != null)
            return this.target.getDPI();
        return -1f;
    }

    public String getBaseScreenshot () {
        if (this.base != null && this.base.getScreenshot() != null)
            return this.base.getScreenshot().getPath();
        return null;
    }

    public String getTargetScreenshot () {
        if (this.target != null && this.target.getScreenshot() != null)
            return this.target.getScreenshot().getPath();
        return null;
    }

    private int getBaseX () {
        if (this.base != null)
            return this.base.getX();
        return -1;
    }

    private int getTargetX () {
        if (this.target != null)
            return this.target.getX();
        return -1;
    }

    private int getBaseY () {
        if (this.base != null)
            return this.base.getY();
        return -1;
    }

    private int getTargetY () {
        if (this.target != null)
            return this.target.getY();
        return -1;
    }

    private int getBaseParentX () {
        if (this.base != null)
            return this.base.getParentX();
        return -1;
    }

    private int getTargetParentX () {
        if (this.target != null)
            return this.target.getParentX();
        return -1;
    }

    private int getBaseParentY () {
        if (this.base != null)
            return this.base.getParentY();
        return -1;
    }

    private int getTargetParentY () {
        if (this.target != null)
            return this.target.getParentY();
        return -1;
    }

    private int getBaseWidth () {
        if (this.base != null)
            return this.base.getWidth();
        return -1;
    }

    private int getTargetWidth () {
        if (this.target != null)
            return this.target.getWidth();
        return -1;
    }

    private int getBaseHeight () {
        if (this.base != null)
            return this.base.getHeight();
        return -1;
    }

    private int getTargetHeight () {
        if (this.target != null)
            return this.target.getHeight();
        return -1;
    }

    private int getBaseDeviceWidth () {
        if (this.base != null)
            return this.base.getDeviceWidth();
        return -1;
    }

    private int getTargetDeviceWidth () {
        if (this.target != null)
            return this.target.getDeviceWidth();
        return -1;
    }

    private int getBaseViewportWidth () {
        if (this.base != null)
            return this.base.getViewportWidth();
        return -1;
    }

    private int getTargetViewportWidth () {
        if (this.target != null)
            return this.target.getViewportWidth();
        return -1;
    }

    private String getXPath () {
        if (this.target != null)
            return this.target.getXPath();
        return this.base.getXPath();
    }

    private String getBaseXPath () {
        return (this.base == null ? null : this.base.getXPath());
    }

    private String getTargetXPath () {
        return (this.target == null ? null : this.target.getXPath());
    }

    private int getTargetPreviousSiblingLeft () {
        if (this.target != null)
            return this.target.getPreviousSiblingLeft();
        return -1;
    }
    private int getTargetPreviousSiblingTop () {
        if (this.target != null)
            return this.target.getPreviousSiblingTop();
        return -1;
    }
    private int getTargetNextSiblingLeft () {
        if (this.target != null)
            return this.target.getNextSiblingLeft();
        return -1;
    }
    private int getTargetNextSiblingTop () {
        if (this.target != null)
            return this.target.getNextSiblingTop();
        return -1;
    }
    private int getTargetTextNodes () {
        if (this.target != null)
            return this.target.getTextNodes();
        return -1;
    }
    private String getTargetFontFamily () {
        if (this.target != null)
            return this.target.getFontFamily();
        return null;
    }

    private int getBasePreviousSiblingLeft () {
        if (this.base != null)
            return this.base.getPreviousSiblingLeft();
        return -1;
    }
    private int getBasePreviousSiblingTop () {
        if (this.base != null)
            return this.base.getPreviousSiblingTop();
        return -1;
    }
    private int getBaseNextSiblingLeft () {
        if (this.base != null)
            return this.base.getNextSiblingLeft();
        return -1;
    }
    private int getBaseNextSiblingTop () {
        if (this.base != null)
            return this.base.getNextSiblingTop();
        return -1;
    }
    private int getBaseTextNodes () {
        if (this.base != null)
            return this.base.getTextNodes();
        return -1;
    }
    private String getBaseFontFamily () {
        if (this.base != null)
            return this.base.getFontFamily();
        return null;
    }

    public String toRow() {
        return String.format("%s,%d,%s,%d,%d,\"%s\",\"%s\",%s,%s,%.1f,%.1f,%s,%s," +
                             "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d," +
                             "%.1f,%.1f,%d,%d,%d,%d,%s,%s,%s,%.1f," +
                             "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s",
                             this.getURL(), this.getId(), this.getTagName(),
                             this.getChildsNumber(), this.getTextLength(),
                             this.getBasePlatform(), this.getTargetPlatform(),
                             null, null,
                             this.getBaseDPI(), this.getTargetDPI(),
                             this.getBaseScreenshot(), this.getTargetScreenshot(),
                             this.getBaseX(), this.getTargetX(),
                             this.getBaseY(), this.getTargetY(),
                             this.getBaseHeight(), this.getTargetHeight(),
                             this.getBaseWidth(), this.getTargetWidth(),
                             this.getBaseParentX(), this.getTargetParentX(),
                             this.getBaseParentY(), this.getTargetParentY(),
                             this.imageDiff, this.chiSquared,
                             this.getBaseDeviceWidth(), this.getTargetDeviceWidth(),
                             this.getBaseViewportWidth(), this.getTargetViewportWidth(),
                             this.getXPath(),this.getBaseXPath(), this.getTargetXPath(),
                             this.phash,
                             this.getBasePreviousSiblingLeft(), this.getTargetPreviousSiblingLeft(),
                             this.getBasePreviousSiblingTop(), this.getTargetPreviousSiblingTop(),
                             this.getBaseNextSiblingLeft(), this.getTargetNextSiblingLeft(),
                             this.getBaseNextSiblingTop(), this.getTargetNextSiblingTop(),
                             this.getBaseTextNodes(), this.getTargetTextNodes(),
                             this.getBaseFontFamily(), this.getTargetFontFamily());
    }

    public static String header() {
        return "@RELATION browserninja.website\n" +
               "@ATTRIBUTE URL STRING\n" +
               "@ATTRIBUTE id NUMERIC\n" +
               "@ATTRIBUTE tagName STRING\n" +
               "@ATTRIBUTE childsNumber NUMERIC\n" +
               "@ATTRIBUTE textLength NUMERIC\n" +
               "@ATTRIBUTE basePlatform STRING\n" +
               "@ATTRIBUTE targetPlatform STRING\n" +
               "@ATTRIBUTE baseBrowser STRING\n" +
               "@ATTRIBUTE targetBrowser STRING\n" +
               "@ATTRIBUTE baseDPI NUMERIC\n" +
               "@ATTRIBUTE targetDPI NUMERIC\n" +
               "@ATTRIBUTE baseScreenshot STRING\n" +
               "@ATTRIBUTE targetScreenshot STRING\n" +
               "@ATTRIBUTE baseX NUMERIC\n" +
               "@ATTRIBUTE targetX NUMERIC\n" +
               "@ATTRIBUTE baseY NUMERIC\n" +
               "@ATTRIBUTE targetY NUMERIC\n" +
               "@ATTRIBUTE baseHeight NUMERIC\n" +
               "@ATTRIBUTE targetHeight NUMERIC\n" +
               "@ATTRIBUTE baseWidth NUMERIC\n" +
               "@ATTRIBUTE targetWidth NUMERIC\n" +
               "@ATTRIBUTE baseParentX NUMERIC\n" +
               "@ATTRIBUTE targetParentX NUMERIC\n" +
               "@ATTRIBUTE baseParentY NUMERIC\n" +
               "@ATTRIBUTE targetParentY NUMERIC\n" +
               "@ATTRIBUTE imageDiff NUMERIC\n" +
               "@ATTRIBUTE chiSquared NUMERIC\n" +
               "@ATTRIBUTE baseDeviceWidth NUMERIC\n" +
               "@ATTRIBUTE targetDeviceWidth NUMERIC\n" +
               "@ATTRIBUTE baseViewportWidth NUMERIC\n" +
               "@ATTRIBUTE targetViewportWidth NUMERIC\n" +
               "@ATTRIBUTE xpath STRING\n" +
               "@ATTRIBUTE baseXpath STRING\n" +
               "@ATTRIBUTE targetXpath STRING\n" +
               "@ATTRIBUTE phash NUMERIC\n" +
               "@ATTRIBUTE basePreviousSiblingLeft NUMERIC\n" +
               "@ATTRIBUTE targetPreviousSiblingLeft NUMERIC\n" +
               "@ATTRIBUTE basePreviousSiblingTop NUMERIC\n" +
               "@ATTRIBUTE targetPreviousSiblingTop NUMERIC\n" +
               "@ATTRIBUTE baseNextSiblingLeft NUMERIC\n" +
               "@ATTRIBUTE targetNextSiblingLeft NUMERIC\n" +
               "@ATTRIBUTE baseNextSiblingTop NUMERIC\n" +
               "@ATTRIBUTE targetNextSiblingTop NUMERIC\n" +
               "@ATTRIBUTE baseTextNodes NUMERIC\n" +
               "@ATTRIBUTE targetTextNodes NUMERIC\n" +
               "@ATTRIBUTE baseFontFamily STRING\n" +
               "@ATTRIBUTE targetFontFamily STRING\n" +
               "@DATA";
    }
}
