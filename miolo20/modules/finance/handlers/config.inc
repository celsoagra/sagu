<?php

/**
 * <--- Copyright 2005-2010 de Solis - Cooperativa de Solu��es Livres Ltda.
 * 
 * Este arquivo � parte do programa Sagu.
 * 
 * O Sagu � um software livre; voc� pode redistribu�-lo e/ou modific�-lo
 * dentro dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o
 * do Software Livre (FSF); na vers�o 2 da Licen�a.
 * 
 * Este programa � distribu�do na esperan�a que possa ser �til, mas SEM
 * NENHUMA GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO
 * ou APLICA��O EM PARTICULAR. Veja a Licen�a P�blica Geral GNU/GPL em
 * portugu�s para maiores detalhes.
 * 
 * Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU, sob o t�tulo
 * "LICENCA.txt", junto com este programa, se n�o, acesse o Portal do Software
 * P�blico Brasileiro no endere�o www.softwarepublico.gov.br ou escreva para a
 * Funda��o do Software Livre (FSF) Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA --->
 * 
 * Finance config handler.
 * Contains the menus to access config submenus
 *
 * @author Daniel Afonso Heisler [daniel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 *
 * @since
 * Class created on 28/07/2006
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess('finConfig', A_ACCESS, true, true);

$function = MIOLO::_request('function');
if ( $function == 'resetStack' )
{
    SAGU::resetStack();
}

$home = 'main:config';
$navbar->addOption(_M('Configura��o', $module), $module, $home, null, array('function'=>'resetStack'));

if ( !$MIOLO->invokeHandler($module, 'config/' . $context->shiftAction()) )
{

    $ui        = $MIOLO->getUI();
    $btnClose = $MIOLO->getActionURL($module,substr($home,0,strrpos($home,':')));

    $icon        = $ui->getImage($module,'config-16x16.png');
    $pnlFinance = new MActionPanel('pnlFinance', _M('Configura��o', $module), null, $btnClose, $icon);
    $pnlFinance->setIconType('small');
    $pnlFinance->setControlSize(SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_WIDTH'),SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_HEIGHT'));

    $menuItem = array (
            array (_M('Mensagem do t�tulo' , $module), 'invoiceMessage-16x16.png', "$home:invoiceMessage"),
            array (_M('Configura��o de negocia��o de t�tulos' , $module), 'defaulter-16x16.png', "$home:invoiceNegotiationConfig")
    );

    $sortMenuItem = SAGU::arraySort($menuItem, 0);
    foreach ( $sortMenuItem as $m )
    {
       $pnlFinance->addAction($m[0], $ui->getImage($module,$m[1]), $module, $m[2], $m[3], $m[4]);
    }

    $theme->clearContent();
    $theme->insertContent($pnlFinance);

}

?>
